#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<string> mat(n);
    for(auto &x : mat) cin >> x;

    vector<vector<int>> good(n,vector<int>(m));
    queue<array<int,2>> q;

    for(int i = 0; i < m; i++) {
        if(mat[0][i] == 'U') {
            q.push({0,i});
        }
        if(mat[n-1][i] == 'D') {
            q.push({n-1,i});
        }
    }
    for(int i = 0; i < n; i++) {
        if(mat[i][0] == 'L') {
            q.push({i,0});
        }
        if(mat[i][m-1] == 'R') {
            q.push({i,m-1});
        }
    }
    while(q.size()) {
        auto [r, c] = q.front();
        q.pop();
        if(good[r][c]) continue;
        good[r][c] = 1;
        if(r && mat[r-1][c] == 'D') {
            q.push({r-1,c});
        }
        if(c && mat[r][c-1] == 'R') {
            q.push({r,c-1});
        }
        if(r != n - 1 && mat[r+1][c] == 'U') {
            q.push({r+1,c});
        }
        if(c != m - 1 && mat[r][c+1] == 'L') {
            q.push({r,c+1});
        }
    }

    // cout << good << '\n';


    int res = 0;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < m; c++) {
            if(mat[r][c] == '?') {
                int f = 1;
                if(r && !good[r-1][c]) {
                    f = 0;
                }
                if(c && !good[r][c-1]) {
                    f = 0;
                }
                if(r != n - 1 && !good[r+1][c]) {
                    f = 0;
                }
                if(c != m - 1 && !good[r][c+1]) {
                    f = 0;
                }
                good[r][c] = f;
            }
            res += good[r][c];
        }
    }

    // cout << good << '\n';

    cout << n * m - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}