#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int SIZE = 26;

struct Trie {
    struct Trie *arr[SIZE];
    int words;
};

struct Trie* getNode() {
    struct Trie* node = new Trie;
    node->words = 0;
    for(int i = 0; i < SIZE; i++) {
        node->arr[i] = NULL;
    }
    return node;
}

void insert(struct Trie* root, string add) {
    struct Trie* curr = root;
    for(int i = 0; i < add.size(); i++) {
        if(!curr->arr[add[i] - 'a']) {
            curr->arr[add[i] - 'a'] = getNode();
        }
        curr = curr->arr[add[i] - 'a'];
        curr->words++;
    }
}

int previous(struct Trie* root, string word) {
    struct Trie* curr = root;
    for(int i = 0; i < word.size(); i++) {
        if(!curr->arr[word[i] - 'a']) {
            return 0;
        }
        curr = curr->arr[word[i] - 'a'];
    }
    return curr->words;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    struct Trie* root = getNode();
    int n; cin >> n;
    while(n-->0) {
        string word; cin >> word;
        insert(root,word);
        cout << previous(root,word) - 1 << "\n";
    }

    return 0;
}