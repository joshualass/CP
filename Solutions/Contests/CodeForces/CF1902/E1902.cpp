#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int SIZE = 26;

struct Trie {
    struct Trie* arr[SIZE];
    int cnt;
};

struct Trie* getNode() {
    struct Trie* node = new Trie;
    node->cnt = false;
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
        curr->cnt++;
    }
    // curr->cnt++;
}

ll query(struct Trie* root, string str) {
    struct Trie* curr = root;
    ll score = 0;
    for(int i = 0; i < str.size(); i++) {
        if(curr != nullptr) {
            curr = curr->arr[str[i] - 'a'];
        }
        if(curr != nullptr) {
            score += curr->cnt;
        }
    }
    return score;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    
    vector<string> v(n);

    for(auto &x: v) cin >> x;

    Trie* root = getNode();
    ll ans = 0;
    for(auto x : v) {
        insert(root, x);
        ans += x.size() * n * 2;
    }
    // cout << "ans : " << ans << '\n';
    for(int i = 0; i < n; i++) {
        string str = v[i];
        reverse(str.begin(), str.end());
        // cout << "str : " << str << "query val : " << query(root,str) << '\n';
        ans -= query(root, str) * 2;
    }
    cout << ans << '\n';
    return 0;
}