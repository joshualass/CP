N = int(input()); prev = -1; cnt = 0
for _ in range(N):
    next = input()
    if next == prev:
        cnt += 1
    prev = next

print(cnt)