import sys

tc = int(input())

for _ in range(tc):

    n = int(input())

    num = -1

    if n == 4:
        # print(2025)
        num = 45
    elif n == 5:
        # print(42025)
        num = 205
    elif n == 6:
        # print(224955)
        num = 795
    else:

        if n & 1:
            # print("1" + ("0" * ((n - 7) // 2)) + "205")
            num = int("1" + ("0" * ((n - 7) // 2)) + "205")
        else:
            # print("4" + ("0" * ((n - 8) // 2)) + "205")
            num = int("4" + ("0" * ((n - 8) // 2)) + "205")

    sys.stdout.write(str(num * num) + "\n")

        # sys.stdout.write(str(num) + "\n")

        # l = 10 ** max(0, (n - 5) // 2)
        # r = 10 ** ((n - 1) // 2)

        # while l != r:
        #     m = (l + r) // 2
        #     num = m * 1000 + 205
        #     le = len(str(num * num))
        #     # print("l",l,"r",r,"m",m,"le",le)
        #     if le == n:
        #         l = m
        #         r = m
        #     elif le > n:
        #         r = m - 1
        #     else:
        #         l = m + 1

        # num = (l * 1000 + 205) ** 2

        # print((l * 1000 + 205) ** 2)



# with open("gg", "w") as gg:

#     for i in range(4, 1001):

#         n = i

#         if n == 4:
#             print(2025)
#             gg.write()
#         else:
#             l = 0
#             r = 10 ** n

#             while l != r:
#                 m = (l + r) // 2
#                 num = m * 1000 + 205
#                 le = len(str(num * num))
#                 # print("l",l,"r",r,"m",m,"le",le)
#                 if le == n:
#                     l = m
#                     r = m
#                 elif le > n:
#                     r = m - 1
#                 else:
#                     l = m + 1

#             gg.write("\""+str((l * 1000 + 205) ** 2)+"\",")

