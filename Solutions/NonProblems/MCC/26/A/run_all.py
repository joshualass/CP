#!/usr/bin/env python3
"""Compile, run, score, and keep the best outputs.

Usage:
    python3 run_all.py

By default, this reads tests/01, tests/02, ..., tests/08. Candidate outputs are
written to candidates/. A candidate replaces outputs/XX.out only when it has a
strictly lower raw score than the saved output. The saved outputs are bundled
into outputs.zip.
"""

from __future__ import annotations

import argparse
import math
import os
import shutil
import subprocess
import zipfile
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent
SOLVER = ROOT / "solver"
OUTPUT_DIR = ROOT / "outputs"
CANDIDATE_DIR = ROOT / "candidates"
DEFAULT_TEST_DIR = ROOT / "tests"
MAX_TICKS = 1_000_000
MAX_MOVES = 2_000_000
PENALTY = {
    1: 1.0,
    2: 1.05,
    3: 1.2,
    4: 1.5,
}


@dataclass
class TestCase:
    vertices: int
    edges: set[tuple[int, int]]
    train_count: int
    train_start: list[int]
    capacity: int
    starts: list[int]
    dests: list[int]
    appears: list[int]


@dataclass
class ScoreResult:
    valid: bool
    score: float
    reason: str = ""


def compile_solver() -> None:
    subprocess.run(
        [
            "g++",
            "-std=c++17",
            "-O2",
            "-pipe",
            "-Wall",
            "-Wextra",
            "main.cpp",
            "-o",
            str(SOLVER),
        ],
        cwd=ROOT,
        check=True,
    )


def find_input(input_dir: Path, test_id: str) -> Path | None:
    candidates = [
        input_dir / test_id,
        input_dir / f"{test_id}.in",
        input_dir / f"{test_id}.txt",
    ]
    for candidate in candidates:
        if candidate.exists():
            return candidate
    return None


def read_test(input_file: Path) -> TestCase:
    data = list(map(int, input_file.read_text().split()))
    pos = 0

    def take() -> int:
        nonlocal pos
        if pos >= len(data):
            raise ValueError(f"unexpected end of input in {input_file}")
        value = data[pos]
        pos += 1
        return value

    vertices = take()
    edge_count = take()
    edges: set[tuple[int, int]] = set()
    for _ in range(edge_count):
        u = take()
        v = take()
        edges.add((min(u, v), max(u, v)))

    train_count = take()
    train_start = [0] + [take() for _ in range(train_count)]
    capacity = take()

    people_count = take()
    starts = [0] * (people_count + 1)
    dests = [0] * (people_count + 1)
    appears = [0] * (people_count + 1)
    for i in range(1, people_count + 1):
        starts[i] = take()
        dests[i] = take()
        appears[i] = take()

    if pos != len(data):
        raise ValueError(f"extra integers at end of {input_file}")

    return TestCase(
        vertices=vertices,
        edges=edges,
        train_count=train_count,
        train_start=train_start,
        capacity=capacity,
        starts=starts,
        dests=dests,
        appears=appears,
    )


def parse_int_line(lines: list[str], cursor: int, what: str) -> tuple[int, int]:
    if cursor >= len(lines):
        raise ValueError(f"missing {what}")
    parts = lines[cursor].split()
    if len(parts) != 1:
        raise ValueError(f"bad {what}: {lines[cursor]!r}")
    return int(parts[0]), cursor + 1


def parse_output(output_file: Path) -> tuple[list[tuple[list[tuple[str, int, int]], list[tuple[int, int]]]], int]:
    lines = output_file.read_text().splitlines()
    cursor = 0
    ticks, cursor = parse_int_line(lines, cursor, "tick count")
    if ticks < 0 or ticks > MAX_TICKS:
        raise ValueError(f"tick count {ticks} exceeds limit {MAX_TICKS}")

    plan: list[tuple[list[tuple[str, int, int]], list[tuple[int, int]]]] = []
    total_moves = 0
    for tick in range(1, ticks + 1):
        action_count, cursor = parse_int_line(lines, cursor, f"action count at tick {tick}")
        if action_count < 0:
            raise ValueError(f"negative action count at tick {tick}")

        actions: list[tuple[str, int, int]] = []
        for _ in range(action_count):
            if cursor >= len(lines):
                raise ValueError(f"missing action at tick {tick}")
            parts = lines[cursor].split()
            cursor += 1
            if len(parts) != 3 or parts[0] not in {"pick", "drop"}:
                raise ValueError(f"bad action at tick {tick}: {' '.join(parts)!r}")
            actions.append((parts[0], int(parts[1]), int(parts[2])))

        move_count, cursor = parse_int_line(lines, cursor, f"move count at tick {tick}")
        if move_count < 0:
            raise ValueError(f"negative move count at tick {tick}")
        total_moves += move_count
        if total_moves > MAX_MOVES:
            raise ValueError(f"move count exceeds limit {MAX_MOVES}")

        moves: list[tuple[int, int]] = []
        for _ in range(move_count):
            if cursor >= len(lines):
                raise ValueError(f"missing move at tick {tick}")
            parts = lines[cursor].split()
            cursor += 1
            if len(parts) != 2:
                raise ValueError(f"bad move at tick {tick}: {' '.join(parts)!r}")
            moves.append((int(parts[0]), int(parts[1])))

        plan.append((actions, moves))

    if any(line.strip() for line in lines[cursor:]):
        raise ValueError("non-empty trailing lines after plan")

    return plan, total_moves


def score_output(test: TestCase, output_file: Path) -> ScoreResult:
    try:
        plan, _ = parse_output(output_file)
        people_count = len(test.starts) - 1
        train_pos = test.train_start[:]
        onboard_train = [0] * (people_count + 1)
        person_city = test.starts[:]
        ride_count = [0] * (people_count + 1)
        arrival = [0] * (people_count + 1)
        train_load = [0] * (test.train_count + 1)

        for tick, (actions, moves) in enumerate(plan, start=1):
            for command, train_id, person_id in actions:
                if not 1 <= train_id <= test.train_count:
                    raise ValueError(f"tick {tick}: train id out of range: {train_id}")
                if not 1 <= person_id <= people_count:
                    raise ValueError(f"tick {tick}: tradesman id out of range: {person_id}")

                if command == "pick":
                    if arrival[person_id] != 0:
                        raise ValueError(f"tick {tick}: picking completed tradesman {person_id}")
                    if onboard_train[person_id] != 0:
                        raise ValueError(f"tick {tick}: tradesman {person_id} already on a train")
                    if tick < test.appears[person_id]:
                        raise ValueError(f"tick {tick}: tradesman {person_id} has not appeared")
                    if person_city[person_id] != train_pos[train_id]:
                        raise ValueError(f"tick {tick}: train {train_id} and tradesman {person_id} are in different cities")
                    if train_load[train_id] >= test.capacity:
                        raise ValueError(f"tick {tick}: train {train_id} exceeds capacity")

                    ride_count[person_id] += 1
                    if ride_count[person_id] > 4:
                        raise ValueError(f"tick {tick}: tradesman {person_id} takes more than four rides")
                    onboard_train[person_id] = train_id
                    person_city[person_id] = 0
                    train_load[train_id] += 1

                else:
                    if onboard_train[person_id] != train_id:
                        raise ValueError(f"tick {tick}: tradesman {person_id} is not on train {train_id}")

                    onboard_train[person_id] = 0
                    train_load[train_id] -= 1
                    person_city[person_id] = train_pos[train_id]
                    if person_city[person_id] == test.dests[person_id]:
                        arrival[person_id] = tick

            moving_trains: set[int] = set()
            moving_edges: set[tuple[int, int]] = set()
            new_positions = train_pos[:]
            for train_id, city in moves:
                if not 1 <= train_id <= test.train_count:
                    raise ValueError(f"tick {tick}: moving train id out of range: {train_id}")
                if not 1 <= city <= test.vertices:
                    raise ValueError(f"tick {tick}: destination city out of range: {city}")
                if train_id in moving_trains:
                    raise ValueError(f"tick {tick}: train {train_id} moves more than once")
                moving_trains.add(train_id)

                edge = (min(train_pos[train_id], city), max(train_pos[train_id], city))
                if edge not in test.edges:
                    raise ValueError(f"tick {tick}: train {train_id} moves along missing edge {edge}")
                if edge in moving_edges:
                    raise ValueError(f"tick {tick}: multiple trains use edge {edge}")
                moving_edges.add(edge)
                new_positions[train_id] = city

            train_pos = new_positions

        total = 0.0
        for person_id in range(1, people_count + 1):
            if arrival[person_id] == 0:
                raise ValueError(f"tradesman {person_id} never reaches destination")
            total += (arrival[person_id] - test.appears[person_id]) * PENALTY[ride_count[person_id]]

        return ScoreResult(valid=True, score=math.sqrt(total))
    except Exception as exc:
        return ScoreResult(valid=False, score=math.inf, reason=str(exc))


def run_one(input_file: Path, output_file: Path, strategy: int) -> None:
    env = os.environ.copy()
    env["STRATEGY"] = str(strategy)
    with input_file.open("rb") as stdin, output_file.open("wb") as stdout:
        subprocess.run(
            [str(SOLVER)],
            stdin=stdin,
            stdout=stdout,
            cwd=ROOT,
            check=True,
            env=env,
        )


def zip_outputs() -> None:
    archive = ROOT / "outputs.zip"
    with zipfile.ZipFile(archive, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        for out_file in sorted(OUTPUT_DIR.glob("*.out")):
            zf.write(out_file, arcname=out_file.name)


def score_label(result: ScoreResult) -> str:
    if result.valid:
        return f"{result.score:.6f}"
    return f"invalid ({result.reason})"


def parse_strategies(value: str) -> list[int]:
    strategies: list[int] = []
    for part in value.split(","):
        part = part.strip()
        if part:
            strategies.append(int(part))
    if not strategies:
        raise ValueError("at least one strategy is required")
    return strategies


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "input_dir",
        nargs="?",
        type=Path,
        default=DEFAULT_TEST_DIR,
        help="directory containing tests named 01, 02, ..., 08",
    )
    parser.add_argument(
        "--force",
        action="store_true",
        help="overwrite saved outputs even when the candidate score is not better",
    )
    parser.add_argument(
        "--strategies",
        default="0,1,2,3,4,5,6,7,8",
        help="comma-separated STRATEGY values to try for each test",
    )
    args = parser.parse_args()

    input_dir = args.input_dir.resolve()
    if not input_dir.exists():
        raise SystemExit(f"input directory not found: {input_dir}")

    OUTPUT_DIR.mkdir(exist_ok=True)
    CANDIDATE_DIR.mkdir(exist_ok=True)

    compile_solver()
    strategies = parse_strategies(args.strategies)

    for i in range(1, 9):
        test_id = f"{i:02d}"
        input_file = find_input(input_dir, test_id)
        if input_file is None:
            print(f"{test_id}: skipping, input file not found")
            continue

        test = read_test(input_file)
        saved_file = OUTPUT_DIR / f"{test_id}.out"
        saved = score_output(test, saved_file) if saved_file.exists() else ScoreResult(False, math.inf, "missing")

        best_candidate = ScoreResult(False, math.inf, "no candidate")
        best_candidate_file: Path | None = None
        best_strategy = -1

        for strategy in strategies:
            strategy_file = CANDIDATE_DIR / f"{test_id}.s{strategy}.out"
            run_one(input_file, strategy_file, strategy)
            candidate = score_output(test, strategy_file)
            print(f"{test_id} strategy {strategy}: {score_label(candidate)}")

            if candidate.valid and candidate.score < best_candidate.score:
                best_candidate = candidate
                best_candidate_file = strategy_file
                best_strategy = strategy

        candidate_file = CANDIDATE_DIR / f"{test_id}.out"
        if best_candidate_file is not None:
            shutil.copyfile(best_candidate_file, candidate_file)

        should_replace = args.force or (best_candidate.valid and best_candidate.score < saved.score)
        if should_replace:
            if best_candidate_file is None:
                raise RuntimeError(f"{test_id}: no valid candidate to save")
            shutil.copyfile(best_candidate_file, saved_file)
            action = "saved"
        else:
            action = "kept"

        print(
            f"{test_id}: best_candidate=s{best_strategy} {score_label(best_candidate)} "
            f"previous={score_label(saved)} -> {action}"
        )

    zip_outputs()
    print("wrote outputs.zip from saved outputs")


if __name__ == "__main__":
    main()
