n = int(input())
a = input().split(" ")

s = []

for ttfang in a:
    num = int(ttfang)
    while(len(s) > 0 and num > s[-1]):
        s = s[0:-1]
    while(len(s) > 0 and num == s[-1]):
        s = s[0:-1]
        num *= 2
    s.append(num)
    
    # print("s",s)

print(s[0])