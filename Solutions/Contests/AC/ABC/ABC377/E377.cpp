#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll binexp(ll base, ll power, ll mod = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%mod;
        }
        base = base*base%mod;
        power >>= 1;
    }
    return ans;
}

int lifts[20][200000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        int p; cin >> p;
        p--;
        lifts[0][i] = p;
    }

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[i][j] = lifts[i-1][lifts[i-1][j]];
        }
    }

    vector<int> vis(n);
    vector<int> moveamt(n);
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            int cur = i;
            vector<int> in_cycle;
            while(vis[cur] == 0) {
                in_cycle.push_back(cur);
                vis[cur] = 1;
                cur = lifts[0][cur];
            }
            int sz = in_cycle.size();
            // cout << "sz : " << sz << '\n';
            // cout << "2 : " << 2 << " k : " << k << " sz : " << sz << '\n';
            ll liftcnt = binexp(2,k,sz);
            for(int x : in_cycle) {
                moveamt[x] = liftcnt;
            }
            
        }
    }

    // // cout << "moveamtn : " << moveamt << '\n';

    for(int i = 0; i < n; i++) {
        int cur = i;
        for(int bit = 0; bit < 20; bit++) {
            if((moveamt[i] >> bit) & 1) {
                cur = lifts[bit][cur];
            }
        }
        cout << cur + 1 << " \n"[i == n - 1];
    }

    return 0;
}