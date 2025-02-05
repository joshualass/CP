#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
in order to get this to work, had to store 2 strings at each trie node. 
Did not work to store the lexicographically smallest string 
*/

struct TrieNode {
    vector<string> s;
    TrieNode* c[26];
    TrieNode() {
        for(int i = 0; i < 26; i++) {
            c[i] = nullptr;
        }
    }
};

void inserts(vector<string> &a, string s) {
    if(a.size() < 2) {
        a.push_back(s);
        if(a.size() == 2 && a[1] < a[0]) swap(a[0],a[1]);
    } else {
        if(s < a[0]) {
            a[1] = a[0];
            a[0] = s;
        } else if(s < a[1]) {
            a[1] = s;
        }
    }
}

void insert(string s, TrieNode* root) {
    TrieNode* curr = root;
    inserts(curr->s, s);
    for(int i = s.size() - 1; i >= 0; i--) {
        if(curr->c[s[i] - 'a'] == nullptr) {
            curr->c[s[i] - 'a'] = new TrieNode();
        }
        assert(curr->c[s[i] - 'a'] != nullptr);
        curr = curr->c[s[i] - 'a'];
        inserts(curr->s, s);
    }
}

string query(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(int i = s.size() - 1; i >= 0; i--) { //iterate over characters in suffix
        if(curr->c[s[i] - 'a'] != nullptr && (curr->c[s[i] - 'a']->s.size() > 1  || curr->c[s[i] - 'a']->s[0] != s)) { //see if there exists a child with the next matching character that is not equal to the current word. 
            curr = curr->c[s[i] - 'a'];
        } else { //no further rhyming children
            break;
        }
    }
    if(curr->s[0] != s) return curr->s[0];
    return curr->s[1];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    TrieNode* root = new TrieNode();
    while(1) {
        string s;
        getline(cin, s);
        if(s.size() == 0) break;
        insert(s, root);
    }

    while(1) {
        string s, tmp;
        getline(cin, s);
        if(s.size() == 0) break;
        cout << query(s, root) << '\n';
    }

    return 0;
}