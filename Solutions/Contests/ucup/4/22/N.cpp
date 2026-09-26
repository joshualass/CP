#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<int>> solve(int n, int m) {

    if(m >= n) {
        return {};
    } else {
    
        if(n == 2) {
            return {
                {1, 0},
                {0, 1}
            };
        } else if(n == 4 && m == 2) {

            return {
                {1, 1, 1, 0},
                {0, 0, 0, 1},
                {1, 1, 1, 1},
                {1, 0 ,0 ,0}
            };

        } else {
            // cout << "violet1" << endl;

            vector<vector<int>> res(n, vector<int>(n));
            vector<vector<array<int,2>>> rs(n - 2);
            int s = 0;
            for(int i = 0; i < n; i += 2) {
                // cout << "i : " << i << endl;
                int vis = 0;
                for(int j = 0; i / 2 + j + 2 < n; j++) {
                    res[i][j] = 1;
                    // cout << "j : " << j << endl;
                    // cout << "s : " << s << endl;
                    rs[s].push_back({i, j});
                    vis = 1;
                }
                s += vis;
            }

            // cout << "violet2" << endl;

            int col = n - 1, row = 0, cnt = 0;
            while(row < n) {
                res[row][col] = 1;
                cnt++;
                if(cnt == 2) {
                    cnt = 0;
                    col--;
                    res[row][col] = 1;
                }
                row++;
            }

            // cout << "violet3" << endl;
            if(n & 1) s--;

            // cout << "s : " << s << endl;


            for(int i = (n - 1) / 2 * 2; i >= 4; i -= 2) {
                for(int j = n - 1; res[i][j-1] == 0; j--) {
                    // cout << "i : " << i << " j : " << j << endl;
                    res[i][j] = 1;
                    rs[s].push_back({i, j});
                }
                s++;
            }

            // cout << "start res" << endl;
            // for(auto x : res) cout << x << endl;

            int rem = 0;

            if(n % 2 == 0) {
                rem = (n - 2) / 2;
            }

            rs[rem].push_back({0, n - 1});
            rs[rem].push_back({1, n - 1});

            // cout << "rs" << endl;
            // for(auto x : rs) cout << x << endl;

            for(int i = 0; i + m + 1 < n; i++) {
                // cout << "rm i : " << i << endl;
                for(auto [r, c] : rs[i]) res[r][c] = 0;
            }

            return res;
        }

    }

}

bool checker(int n, int m, vvi& g) {

    cout << "testing n : " << n << " m : " << m << endl;

    if(g.empty()) {
        return m >= n;
    } else {
        vvb v(n, vb(n, false));
        vi dr = {-1, 1, 0, 0};
        vi dc = {0, 0, -1, 1};
        function<int(int, int)> dfs = [&](int r, int c) -> int {
            if(v[r][c]) return 0;
            v[r][c] = 1;
            int ans = 1;
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if(g[nr][nc] != g[r][c]) continue;
                ans += dfs(nr, nc);
            }
            return ans;
        };
        set<int> ws, bs;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(v[i][j]) continue;
                if(g[i][j] == 0) {
                    ws.insert(dfs(i, j));
                }
                else if(g[i][j] == 1) {
                    bs.insert(dfs(i, j));
                }
                else {
                    cout << "Unexpected color : " << g[i][j] << "\n";
                    return false;
                }
            }
        }
        if(ws.size() != m) {
            cout << "White components have wrong amount of unique sizes : " << ws.size() << "\n";
            for(auto i : ws) cout << i << " ";
            cout << "\n";
            return false;
        }
        if(bs.size() != m) {
            cout << "Black components have wrong amount of unique sizes : " << bs.size() << "\n";
            for(auto i : bs) cout << i << " ";
            cout << "\n";
            return false;
        }
        return true;
    }
}

const int testing = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(testing == 1) {
        for(int n = 1; n <= 50; n++) {
            for(int m = 1; m <= 50; m++) {
                auto res = solve(n, m);
                if(!checker(n, m, res)) {
                    return 0;
                }
            }
        }
    } else {
        int n, m; cin >> n >> m;
        auto res = solve(n, m);
        // assert(checker(n, m, res));
        if(res.empty()) {
            cout << "-1\n";
        } else {
            for(auto x : res) {
                for(auto y : x) {
                    cout << (y ? '#' : '.');
                }
                cout << '\n';
            }
        }
    }

    return 0;
}
