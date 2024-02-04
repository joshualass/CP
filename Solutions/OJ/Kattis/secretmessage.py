import math

N = int(input())

for _ in range(N):
    s = input()
    size = int(math.sqrt(len(s) - 1e-10)) + 1
    mat = []
    for _ in range(size):
        mat.append(['\0'] * size)

    for i in range(size):
        for j in range(size):
            if(i * size + j < len(s)):
                mat[j][size - 1 - i] = s[i * size + j]

    for i in range(size):
        for j in range(size):
            if(mat[i][j] != '\0'):
                print(mat[i][j], end='')
                
    print()