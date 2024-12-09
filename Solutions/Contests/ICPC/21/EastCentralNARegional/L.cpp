#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;

    auto getcnt = [&]() -> int {
        vector<int> sorted_order;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] != -1) {
                    sorted_order.push_back(a[i][j]);
                }
            }
        }
        sort(sorted_order.begin(),sorted_order.end());
        int saves = 0;
        int cntbefore = 0;
        for(int d = 0; d < n + m - 1; d++) {
            set<int> s;
            for(int row = d, col = 0; row >= 0; row--, col++) {
                if(row >= 0 && row < n & col >= 0 && col < m) {
                    if(a[row][col] != -1) {
                        s.insert(a[row][col]);
                    }
                }
            }
            for(int i = 0; i < s.size(); i++) {
                if(s.count(sorted_order[cntbefore + i])) {
                    saves++;
                }
            }
            cntbefore += s.size();
        }

        // cout << "saves : " << saves << '\n';

        return sorted_order.size() - saves;

    };

    auto rotate = [&]() -> void {
        vector<vector<int>> newmat(m,vector<int>(n));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                newmat[j][n-i-1] = a[i][j];
            }
        }
        swap(n,m);
        a = newmat;
    };

    int res = INT_MAX;
    for(int i = 0; i < 4; i++) {
        res = min(res, getcnt());
        rotate();
    }

    cout << res << '\n';

    return 0;
}