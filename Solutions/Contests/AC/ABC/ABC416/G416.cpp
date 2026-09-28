#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Trie {
    int isend, minch;
    Trie *ch[26];
    Trie() {
        isend = 0, minch = 26;
        for(int i = 0; i < 26; i++) ch[i] = nullptr;
    }
};

void insert(Trie *root, string s) {
    Trie *cur = root;
    for(char c : s) {
        int d = c - 'a';
        if(cur->ch[d] == nullptr) {
            cur->ch[d] = new Trie();
        }
        cur->minch = min(cur->minch, d);
        cur = cur->ch[d];
    }
    cur->isend = 1;
}

string solve(Trie *root, int k) {

    vector<vector<Trie*>> dp(k * 10, vector<Trie*>(10, nullptr));
    vector<vector<int>> wc(k * 10, vector<int>(10, 0));
    string res = "";
    wc[0][0] = 0;
    dp[0][0] = root;

    for(int i = 0; i < k * 10; i++) {
        int nxch = 25;
        for(int j = 0; j < 10; j++) {
            if(dp[i][j] != nullptr) nxch = min(nxch, dp[i][j]->minch);
        }
        res.push_back(nxch + 'a');
        for(int j = 0; j < 10; j++) {
            if(dp[i][j] != nullptr) {
                if(dp[i][j]->minch == nxch) {
                    if(i + 1 < k * 10 && j + 1 < 10) {
                        dp[i+1][j+1] = dp[i][j]->ch[nxch];
                        wc[i+1][j+1] = wc[i][j];
                    }
                    if(dp[i][j]->ch[nxch]->isend) {
                        if(wc[i][j] + 1 == k) {
                            goto done;
                        }
                        dp[i+1][0] = root;
                        wc[i+1][0] = max(wc[i+1][0], wc[i][j] + 1);
                    }
                }
            }
        }
    }

done:
    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    Trie *root = new Trie();
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        insert(root, s);
    }

    cout << solve(root, k) << '\n';

    return 0;
}
