h = int(input())

while True:
    if (h * (h + 1) + h * (h - 1) // 2) % 4 == 0:
        print(h)
        break
    h += 1
     