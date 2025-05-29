
def main():

    n = int(input())

    p2 = 0

    while n % 2 == 0:
        n /= 2
        p2 += 1

    if n == 1:
        print(p2,"/",1,sep="")
        return

    cnt = 0
    l = 1

    first = True

    while first or l != 1:
        first = False
        cnt += 1
        l = l * 2
        if l > n:
            l -= n

    print("cnt",cnt)

    

if __name__ == "__main__":
    main()

# from math import gcd
# import math

# class Frac:
#     def __init__(self, n, d):
#         g = gcd(n, d)
#         self.n = n // g
#         self.d = d // g

#     def __add__(self, other):
#         return Frac(self.n * other.d + self.d * other.n, self.d * other.d)

#     def __mul__(self, other):
#         return Frac(self.n * other.n, self.d * other.d)

# def main():
#     n = int(input())
#     t = (n & -n).bit_length() - 1
#     o = Frac(t, 1)
#     n >>= t

#     p = Frac(1, 1)  # probability of making it this far in the tree
#     r = Frac(0, 1)  # res

#     l = 1

#     pc_mult = []

#     pc_mult.append(1)

#     for _ in range(10005):
#         pc_mult.append(pc_mult[-1] * 2)

#     if n != 1:
#         first = True
#         while first or l != 1:
#             first = False
#             ratio = n / l
#             f = math.ceil(math.log2(ratio))

#             l = l * pc_mult[f]

#             # print(f"n : {n} l : {l} f : {f}")
#             # print(f"p : {p.n}/{p.d}")
#             # print(f"f : {f}")

#             r = r + p * Frac(f, 1)

#             # print(f"upd r : {r.n}/{r.d}")

#             bad = l - n

#             p = p * Frac(bad, l)
#             l = bad

#         # print(f"final r : {r.n}/{r.d}")
#         # print(f"final p : {p.n}/{p.d}")

#         left = Frac(1, 1) + Frac(-1, p.d)

#         # print(f"left p : {left.n}/{left.d}")

#         # print("n", r.n * left.d, "d", r.n * left.d)

#         res = Frac(r.n * left.d, r.d * left.n)

#         # print(f"res : {res.n}/{res.d}")

#         res = res + o

#         print(f"{res.n}/{res.d}")
#     else:
#         print(f"{o.n}/{o.d}")

# if __name__ == "__main__":
#     main()

