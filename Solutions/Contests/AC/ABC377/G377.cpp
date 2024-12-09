#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Trie {
    int lo_min;
    Trie* arr[26];
    Trie() {
        lo_min = 1e9;
        for(int i = 0; i < 26; i++) {
            arr[i] = nullptr;
        }
    }
};

void insert(Trie* root, string word) {
    Trie* curr = root;
    for(int i = 0; i < word.size(); i++) {
        if(curr->arr[word[i] - 'a'] == nullptr) {
            curr->arr[word[i] - 'a'] = new Trie();
        }
        curr = curr->arr[word[i] - 'a'];
        curr->lo_min = min(curr->lo_min, (int) word.size() - i - 1);
    }
}

int query(Trie* root, string word) {
    Trie* curr = root;
    int res = word.size();
    for(int i = 0; i < word.size(); i++) {
        if(curr->arr[word[i] - 'a'] == nullptr) break;
        curr = curr->arr[word[i] - 'a'];
        res = min(res, (int) word.size() - (i + 1) + curr->lo_min);
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    Trie* root = new Trie();
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        cout << query(root, s) << '\n';
        insert(root, s);
    }

    return 0;
}