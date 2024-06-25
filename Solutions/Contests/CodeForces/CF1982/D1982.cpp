#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> heights(n,vector<ll>(m));
    vector<string> caps(n);
    for(auto &x : heights) for(auto &y : x) cin >> y;
    for(auto &x : caps) cin >> x;

    vector<vector<ll>> b(n+1,vector<ll>(m+1));

    ll netsnow = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int add = caps[i][j] == '1' ? 1 : -1;
            b[i+1][j+1] = b[i+1][j] + b[i][j+1] - b[i][j] + add;
            if(caps[i][j] == '0') {
                netsnow -= heights[i][j];
            } else {
                netsnow += heights[i][j];
            }
        }
    }

    // cout << "b?\n" << b;

    ll g = -1;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            
            if(i >= k && j >= k) {
                int square = abs(b[i][j] - b[i-k][j] - b[i][j-k] + b[i-k][j-k]);
                // cout << "i : " << i << " j : " << j << " b[i][j] : " << square << '\n';
                if(square != 0) {
                    if(g == -1) {
                        g = square;
                    } else {
                        g = gcd(g,square);
                    }
                }
            }
        }
    }

    // cout << "netsnow : " << netsnow << " g : " << g << '\n';

    if(netsnow == 0 || g != -1 && abs(netsnow) % g == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}