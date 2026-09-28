n, q = map(int, input().split())

nest = [i for i in range(n)]
revnest = [i for i in range(n)]
in_nest = [i for i in range(n)]

for _ in range(q):
    query = list(map(int, input().split()))
    if query[0] == 1:
        a = query[1]
        b = query[2]

        a -= 1
        b -= 1

        in_nest[a] = nest[b]
    elif query[0] == 2:
        a = query[1]
        b = query[2]

        a -= 1
        b -= 1

        a_idx = nest[a]
        b_idx = nest[b]

        nest[a] = b_idx
        nest[b] = a_idx

        revnest[b_idx] = a
        revnest[a_idx] = b
    elif query[0] == 3:
        a = query[1]
        print(revnest[in_nest[a-1]] + 1)
