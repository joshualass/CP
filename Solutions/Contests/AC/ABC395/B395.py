n = int(input())

for i in range(0, n):
    for j in range(0, n):
        limiting = min(i, j, n - 1 - i, n - 1 - j)
        if limiting % 2 == 0:
            print('#',end='')
        else:
            print('.',end='')
    print()
    