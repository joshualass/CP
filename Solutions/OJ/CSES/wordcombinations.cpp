#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct TrieNode {
    TrieNode* a[26];
    int ends = 0;
    TrieNode() {
        for(int i = 0; i < 26; i++) a[i] = nullptr;
    }
};

void insert(string s, TrieNode* root) {
    TrieNode* curr = root;
    for(char c : s) {
        if(curr->a[c-'a'] == nullptr) {
            curr->a[c-'a'] = new TrieNode();
        }
        curr = curr->a[c-'a'];
    }
    curr->ends++;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    int n = s.size();
    TrieNode* root = new TrieNode();
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        string a; cin >> a;
        reverse(a.begin(), a.end());
        insert(a,root);
    }

    vector<ll> dp(n + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        TrieNode* curr = root;
        for(int j = i - 1; j >= 0; j--) {
            if(curr->a[s[j]-'a'] != nullptr) {
                // cout << "found anything i : " << i << " j : " << j << '\n';
                curr = curr->a[s[j]-'a'];
                dp[i] += dp[j] * curr->ends;
            } else break;
        }
        dp[i] %= MOD;
    }
    // cout << "dp : " << dp << '\n';
    cout << dp[n] << '\n';
    return 0;
}