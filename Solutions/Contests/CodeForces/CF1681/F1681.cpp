#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<array<int,2>>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v, x; cin >> u >> v >> x;
        u--; v--; x--;
        adj[u].push_back({v, x});
        adj[v].push_back({u, x});
    }

    ll res = 0;
    vector<vector<vector<array<int,2>>>> c(n);
    vector<int> ss(n);
    int time = 0;

    auto dfs = [&](auto self, int i, int p, int pc) -> void {
        int s = 1;
        if(pc == -1) {
            for(int j = 0; j < n; j++) {
                c[j].push_back({});
            }
        } else {
            c[pc].push_back({});
        }
        for(auto [c, x] : adj[i]) {
            if(c != p) {
                self(self, c, i, x);
                s += ss[c];
            }
        }
        if(pc == -1) {
            for(int j = 0; j < n; j++) {
                int here = s;
                for(auto [idx, cs] : c[j].back()) {
                    here -= ss[idx];
                }
                for(auto [idx, cs] : c[j].back()) {
                    res += 1LL * cs * here;
                }
            }
        } else {
            int here = s;
            for(auto [idx, cs] : c[pc].back()) {
                here -= ss[idx];
            }
            for(auto [idx, cs] : c[pc].back()) {
                res += 1LL * cs * here;
            }
            c[pc].pop_back();
            c[pc].back().push_back({i, here});
        }
        ss[i] = s;
    };

    dfs(dfs, 0, -1, -1);

    cout << res << '\n';

    return 0;
}

// "exactly once" great!

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// struct FT {
// 	vector<ll> s;
// 	FT(int n) : s(n) {}
// 	void update(int pos, ll dif) { // a[pos] += dif
// 		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
// 	}
// 	ll query(int pos) { // sum of values in [0, pos)
// 		ll res = 0;
// 		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
// 		return res;
// 	}
//     ll query(int l, int r) {
//         return query(r) - query(l);
//     }
// 	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
// 		// Returns n if no sum is >= sum, or -1 if empty sum is.
// 		if (sum <= 0) return -1;
// 		int pos = 0;
// 		for (int pw = 1 << 25; pw; pw >>= 1) {
// 			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
// 				pos += pw, sum -= s[pos-1];
// 		}
// 		return pos;
// 	}
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<vector<array<int,2>>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int u, v, x; cin >> u >> v >> x;
//         u--; v--; x--;
//         adj[u].push_back({v, x});
//         adj[v].push_back({u, x});
//     }

//     vector<int> ss(n), l(n), r(n);
//     vector<vector<array<int,2>>> pars(n);

//     int time = 0;

//     auto dfs = [&](auto self, int i, int p, int d) -> void {
//         int s = 1;
//         l[i] = time++;
//         for(auto [c, x] : adj[i]) {
//             if(c != p) {
//                 self(self, c, i, d + 1);
//                 s += ss[c];
//                 pars[x].push_back({d + 1, c});
//             }
//         }
//         ss[i] = s;
//         r[i] = time;
//     };

//     dfs(dfs, 0, -1, 0);

//     // cout << "l : " << l << " r : " << r << endl;
//     // cout << "pars : " << pars << endl;

//     FT ft(n);

//     ll res = 0;
//     vector<int> upds(n);
//     for(int i = 0; i < n; i++) {
//         if(sz(pars[i])) {
//             pars[i].push_back({0,0});
//             sort(pars[i].rbegin(), pars[i].rend());
//             ll cnt = 0;
//             for(int j = 0; j < sz(pars[i]); j++) {
//                 auto [_, idx] = pars[i][j];
//                 int s = ss[idx] - ft.query(l[idx], r[idx]);
//                 cnt += 1LL * s * (s - 1) / 2;
//                 ft.update(idx, s);
//                 upds[j] = s;
//             }
//             for(int j = 0; j < sz(pars[i]); j++) {
//                 ft.update(pars[i][j][0], - upds[j]);
//             }
//             // cout << "i : " << i << " cnt : " << cnt << endl;
//             res += 1LL * n * (n - 1) / 2 - cnt;
//         }
//     }

//     cout << res << '\n';

//     return 0;
// }
