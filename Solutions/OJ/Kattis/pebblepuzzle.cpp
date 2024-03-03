#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool solve1(vector<vector<int>> cols1, vector<vector<int>> cols2, int rowswap) {
    for(int row = 0; row < cols1[0].size(); row++) {
        swap(cols1[0][row],cols1[rowswap][row]);
        if(cols1[0][row] != cols2[0][row]) {
            for(int col = 0; col < cols1.size(); col++) {
                cols1[col][row] ^= 1;
            }
        }
    }
    sort(cols1.begin(), cols1.end());
    sort(cols2.begin(), cols2.end());
    return cols1 == cols2;
}

void solve() {

    int n, m; cin >> n >> m;
    vector<vector<int>> cols1(m,vector<int>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            string s; cin >> s;
            if(s[0] == 'B') {
                cols1[j][i] = 1;
            }
        }
    }
    vector<vector<int>> cols2(m,vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            string s; cin >> s;
            if(s[0] == 'B') {
                cols2[j][i] = 1;
            }
        }
    }
    bool ok = 0;
    for(int i = 0; i < m; i++) {
        if(solve1(cols1,cols2,i)) {
            // cout << "swapping column i is ok : " << i << '\n';
            ok = 1;
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}