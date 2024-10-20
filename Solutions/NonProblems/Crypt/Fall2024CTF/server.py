from Crypto.Util.number import getPrime, getRandomRange, bytes_to_long, long_to_bytes

FLAG = bytes_to_long(open("flag.txt", "rb").read())

def gen_key():
    p = getPrime(512)
    k = getRandomRange(1, p)
    return p, k

def encrypt(p, k, m):
    m = bytes_to_long(m)
    return long_to_bytes((m * k) % p)

if __name__ == "__main__":
    p, k = gen_key()
    
    print("""Welcome to the SecretPrime online encryption service!""")

    while True:
        print("""    1. Encrypt
    2. Get encrypted flag
              """)
        choice = input("> ")

        if choice == "1":
            m = input("Enter the message to encrypt: ")
            print(f"Encrypted message: {encrypt(p, k, m.encode()).hex()}")
        elif choice == "2":
            print(f"Encrypted flag: {encrypt(p, k, long_to_bytes(FLAG)).hex()}")
            break
        else:
            print("Invalid choice")