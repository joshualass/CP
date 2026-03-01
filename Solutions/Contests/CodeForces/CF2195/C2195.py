tc = int(input())

for _ in range(tc):
    n = int(input())
    a = list(map(int, input().split()))

    dp = [0] * 6

    for num in a:
        num -= 1
        nx = [676767676767] * 6
        for prev_num in range(6):
            for next_num in range(6):
                if prev_num != next_num and next_num + prev_num != 5:
                    nx[next_num] = min(nx[next_num], dp[prev_num] + (0 if next_num == num else 1))
        
        dp = nx

    print(min(dp))