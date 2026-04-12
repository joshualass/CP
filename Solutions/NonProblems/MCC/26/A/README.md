# MCC 26 Starter

This is a deliberately simple multi-train baseline for the train-routing
optimization task.

## What It Does

- Parses one test case from standard input.
- Precomputes shortest-path distances and next hops with BFS.
- Uses a dynamic dispatcher instead of fixed train queues.
- Empty trains choose globally promising pickup cities by estimated delay.
- Loaded trains choose age-aware destinations, and may detour to nearby available pickups when they have spare capacity.
- Supports several heuristic variants through the `STRATEGY` environment variable; `run_all.py` tries multiple variants and keeps the best scored output.
- Lets each train pick up multiple assigned tradesmen at the same city up to capacity `C`.
- Resolves movement conflicts by priority, favoring loaded trains and older onboard passengers.
- Simulates all trains tick by tick and reserves each rail edge before moving, so two trains do not use the same rail in the same movement phase.

The batching is intentionally rough, but trains now draw from global demand
instead of only serving a private assigned queue.

This is still rough, but it is much better than the original single-train
starter and gives you clean hooks for improving assignment and routing.

## Build And Run One Case

```bash
g++ -std=c++17 -O2 -pipe -Wall -Wextra main.cpp -o solver
./solver < 01.in > 01.out
```

## Generate And Keep Best Outputs

Put the official tests in `tests/01`, `tests/02`, ..., `tests/08`, then run:

```bash
python3 run_all.py
```

The script compiles `main.cpp`, runs each test, scores the candidate output,
and only replaces an existing saved output when the candidate has a lower raw
score. It writes:

- `candidates/01.out`, `candidates/02.out`, ...
- `candidates/01.s0.out`, `candidates/01.s1.out`, ...
- `outputs/01.out`, `outputs/02.out`, ...
- `outputs.zip`

You can still pass a different input directory if needed:

```bash
python3 run_all.py path/to/other/tests
```

To overwrite saved outputs regardless of score:

```bash
python3 run_all.py --force
```

The runner tries strategies `0,1,2,3,4,5,6,7,8` by default. Strategies `5+`
spend more work on demand clustering, coordinated empty-train targeting, and
pickup detours. To choose a smaller set:

```bash
python3 run_all.py --strategies 0,2,4
```

## Easy Next Improvements

- Add randomized strategy parameters and run more seeds.
- Tune detour limits by test size and capacity.
- Add route insertion for onboard passengers instead of choosing only the next target greedily.
- Add local search over completed plans or per-train route choices.
