#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//copy jiangly's twosat :)
struct TwoSat {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}
    void addClause(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    bool satisfiable() {
        std::vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};

void solve() {
    int n; cin >> n;
    vector<vector<int>> mat(3,vector<int>(n));
    for(auto &x : mat) for(auto &y : x) cin >> y;

    TwoSat ts(n + 1);

    for(int i = 0; i < n; i++) {
        ts.addClause(abs(mat[0][i]), abs(mat[0][i]) / mat[0][i] == 1, abs(mat[1][i]), abs(mat[1][i]) / mat[1][i] == 1);
        ts.addClause(abs(mat[2][i]), abs(mat[2][i]) / mat[2][i] == 1, abs(mat[1][i]), abs(mat[1][i]) / mat[1][i] == 1);
        ts.addClause(abs(mat[0][i]), abs(mat[0][i]) / mat[0][i] == 1, abs(mat[2][i]), abs(mat[2][i]) / mat[2][i] == 1);
    }
    cout << (ts.satisfiable() ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template <typename T, typename D>
// std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
//     os << '(' << p.first << ", " << p.second << ") ";
//     return os;
// }

// template<typename T, typename D>
// std::ostream& operator<<(std::ostream& os, map<T,D> m) {
//     for(auto &x: m) os << x.first << " " << x.second << " | ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// bool dfs(int i, int v, vector<vector<int>> &mat, vector<int> &a, vector<vector<int>> &adj, int n) {
//     a[i] = v;
//     // cout << "i : " << i << " v : " << v << '\n';
//     // cout << "a : " << a << '\n';
//     bool ok = 1;
//     map<int,int> reqs;
//     for(int c : adj[i]) {
//         int cnt = 0;
//         for(int j = 0; j < 3; j++) {
//             if(a[abs(mat[j][c])] * mat[j][c] < 0) cnt++;
//         }
//         if(cnt > 1) {
//             ok = 0;
//             break;
//         }
//         if(cnt == 1) {
//             for(int j = 0; j < 3; j++) {
//                 if(a[abs(mat[j][c])] == 0) {
//                     reqs[abs(mat[j][c])] = abs(mat[j][c]) / mat[j][c];
//                 }
//             }
//         }
//     }

//     // cout << "reqzzzz : " << reqs << '\n';

//     if(ok) {
//         for(auto [u, v] : reqs) {
//             bool b = dfs(u,v,mat,a,adj,n);
//             if(!b) {
//                 ok = 0;
//                 break;
//             }
//         }
//     }

//     if(!ok) a[i] = 0;
//     // cout << "i : " << i << " ok : " << ok << '\n';
//     return ok;

// }

// void solve(int id) {
//     int n; cin >> n;
//     vector<vector<int>> mat(3,vector<int>(n));
//     vector<int> a(n+1);
//     vector<vector<int>> adj(n+1);
//     for(int i = 0; i < 3; i++) {
//         for(int j = 0; j < n; j++) {
//             cin >> mat[i][j];
//             adj[abs(mat[i][j])].push_back(j);
//         }
//     }
//     if(id == 92) {
//         cout << "n" << n << "_";
//         for(int i = 0; i < 3; i++) {
//             for(int j = 0; j < n; j++) {
//                 cout << mat[i][j] << "_";
//             }
//         }
//     }

//     // for(int i = 0; i <= n; i++) {
//     //     cout << "i : " << i << " adj : " << adj[i] << '\n';
//     // }

//     bool ok = 1;
//     for(int i = 0; i <= n; i++) {
//         if(a[i] == 0) {
//             dfs(i,1,mat,a,adj,n);
//         }
//         if(a[i] == 0) {
//             dfs(i,-1,mat,a,adj,n);
//         }
//         if(a[i] == 0) {
//             ok = 0;
//             break;
//         }
//     }

//     cout << (ok ? "Yes" : "No") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     for(int i = 1; i <= casi; i++) {
//         solve(i);
//     }

//     return 0;
// }