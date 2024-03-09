from sys import stdin
words = []
for line in stdin:
    words.extend(line.strip().split(" "))

myset = set()

# print("length of words: ",len(words))
# print("words:",words)
for i in range(len(words)):
    for j in range(len(words)):
        if i != j:
            myset.add(words[i] + words[j])

mylist = list(myset)
mylist.sort()

for word in mylist:
    print(word)