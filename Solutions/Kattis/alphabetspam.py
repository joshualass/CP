s = input()
N = len(s)
lower = 0
upper = 0
blank = 0
other = 0
for c in s:
    if c >= 'a' and c <= 'z':
        lower += 1
    elif c >= 'A' and c <= 'Z':
        upper += 1
    elif c == '_':
        blank += 1
    else:
        other += 1

print(blank / N)
print(lower / N)
print(upper / N)
print(other / N)