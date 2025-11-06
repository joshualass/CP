s = input()

def solve():
    valid = True
    if s[-1] != 'O':
        valid = False

    for i in range(1, len(s)):
        if s[i - 1] == 'O' and s[i] == 'O':
            valid = False
    
    if valid == False:
        print("INVALID")
        return

    # print("try all the p")

    res = 1 << 500

    for p in range(1, 250):
        start = 1 << p

        ok = True

        for i in range(len(s) - 1, -1, -1):
            c = s[i]

            if c == 'O':
                if start % 2 == 1:
                    ok = False
                    break
                
                start -= 1
                
                if start % 3 != 0:
                    ok = False
                    break

                start //= 3

            elif c == 'E':
                start *= 2

            #if it is currently a power of 2, it is then bad. 
            bc = 0
            c = start
            while c > 0:
                if c % 2 == 1:
                    bc += 1

                c //= 2

            if bc == 1:
                ok = False
                break

        if ok:
            res = min(res, start)

    # print("res",res)

    if res != (1 << 500):
        print(res)
    else:
        print("INVALID")

solve()