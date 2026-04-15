#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ld inf = 1e12;
const ld mx = 1e18;

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

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto self, int i, int p) -> array<ld,2> {
        // cout << "i : " << i << " p : " << p << endl;
        vector<ld> ch;
        ld here = 0;
        for(int c : adj[i]) {
            if(c != p) {
                array<ld,2> a = self(self, c, i);
                here += a[1];
                ch.push_back(a[0] - a[1]);
            }
        }

        // cout << "i : " << i << " here : " << here << " ch : " << ch << endl;

        if(s[i] == '1') {
            // cout << "return here" << endl;
            return {here, here};
        } else {
            sort(ch.begin(), ch.end());

            array<ld,2> res = array<ld,2>{mx, mx};
            for(int j = 0; j < 2; j++) {
                ld add = 0;
                for(int k = -1; k < sz(ch); k++) {
                    if(k != -1) {
                        add += ch[k];
                    }
                    ld n = j + (k + 1), d = sz(adj[i]);
                    if(n == 0) {
                        n = 1;
                        d = inf;
                    }
                    res[j] = min(res[j], here + add + (d / n));
                }
            }

            // cout << "res : " << res << endl;
            return res;
        }

    };

    cout << fixed << setprecision(15) << dfs(dfs, 0, -1)[0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}