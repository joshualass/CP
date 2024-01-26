from sys import stdin
words = []
for line in stdin:
    words.append(line.strip().split(" "))

myset = {}

for i in range(len(words)):
    for j in range(len(words)):
        if i != j:
            myset.add(words[i] + words[j])

for word in myset:
    print(word)