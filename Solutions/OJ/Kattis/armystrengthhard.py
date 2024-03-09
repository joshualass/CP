tc = int(input())

for _ in range(tc):
    trash = input()
    N, M = map(int, input().split())

    godarr = list(map(int, input().split()))
    mecharr = list(map(int, input().split()))

    godmax = -1
    mechmax = -1

    for val in godarr:
        if(val > godmax):
            godmax = val

    for val in mecharr:
        if(val > mechmax):
            mechmax = val

    if godmax >= mechmax:
        print("Godzilla")
    else: 
        print("MechaGodzilla")
