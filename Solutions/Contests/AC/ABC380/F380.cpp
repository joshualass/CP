#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int mult[12];
int dp[531441];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    mult[0] = 1;
    for(int i = 1; i < 12; i++) {
        mult[i] = mult[i-1] * 3;
    }

    fill(begin(dp), end(dp), -1);

    int n, m, l; cin >> n >> m >> l;
    vector<int> A(n + m + l);
    for(int &x : A) cin >> x;

    auto hash = [&](vector<int> &a, vector<int> &b, vector<int> &c) -> int {
        int res = 0;
        for(int x : b) {
            res += mult[x];
        }
        for(int x : c) {
            res += mult[x] * 2;
        }
        return res;
    };

    auto unhash = [&](int x) -> array<vector<int>, 3> {
        vector<int> a, b, c;
        for(int i = 0; i < n + m + l; i++) {
            if(x % 3 == 0) {
                a.push_back(i);
            } else if(x % 3 == 1) {
                b.push_back(i);
            } else {
                c.push_back(i);
            }
            x /= 3;
        }
        return {a,b,c};
    };

    vector<int> as(n), bs(m), cs(l);
    iota(as.begin(), as.end(), 0);
    iota(bs.begin(), bs.end(), n);
    iota(cs.begin(), cs.end(), n + m);

    auto dfs = [&](auto self, int bm) -> int {
        if(dp[bm] != -1) return dp[bm];
        int foundloss = 0;
        auto [a,b,c] = unhash(bm);
        for(int &x : a) {
            for(int &y : c) {
                if(A[y] < A[x]) {
                    swap(x, y);
                    if(self(self, hash(b,a,c)) == 0) foundloss = 1;
                    swap(x,y);
                }
            }
        }
        swap(a,b);
        int tbm = hash(a,b,c);
        for(int x : b) {
            if(self(self, tbm + mult[x]) == 0) foundloss = 1;
        }
        dp[bm] = foundloss;
        // cout << "bm : " << bm << " winning : " << foundloss << '\n';
        return dp[bm];
    };

    cout << (dfs(dfs, hash(as,bs,cs)) ? "Takahashi" : "Aoki") << '\n';

    return 0;
}