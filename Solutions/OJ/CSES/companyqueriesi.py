import sys


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, q = data[0], data[1]

    # parent[x] = direct boss of x.
    # parent[1] = 0 because employee 1 has no boss.
    parent = [0, 0] + data[2:n + 1]

    log = n.bit_length()
    up = [parent]

    # If p[x] is the 2^(j-1)-th ancestor of x, then
    # p[p[x]] is the 2^j-th ancestor.
    for _ in range(1, log):
        p = up[-1]
        up.append(list(map(p.__getitem__, p)))

    # Maps each power of two to its bit index.
    # This avoids calling bit_length() for every set bit of every query.
    bit_index = [0] * (1 << log)
    for j in range(log):
        bit_index[1 << j] = j

    answers = []
    append = answers.append

    pos = n + 1
    end = pos + 2 * q

    while pos < end:
        x = data[pos]
        k = data[pos + 1]
        pos += 2

        # Process only the set bits of k.
        while k and x:
            lowbit = k & -k
            x = up[bit_index[lowbit]][x]
            k -= lowbit

        append(str(x or -1))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()