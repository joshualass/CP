#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}
//use notation of [from][to]. returns value of a * b^pow
vector<vector<ll>> matexp(vector<vector<ll>> a, vector<vector<ll>> b, ll pow) {
    while(pow) {
        if(pow & 1) {
            a = matmult(a,b); //result is the current matrix, mat is the binexp matrix
        }
        b = matmult(b,b);
        pow >>= 1;
    }
    return a;
}

void solve() {
    ll n, x, k; cin >> n >> x >> k;
    ll w = binexp((k * 2 + 1) % MOD, n - 1);
    w = (w * (k+x)) % MOD;
    vector<vector<ll>> a(x, vector<ll>(x)), b(x, vector<ll>(x));

    for(int i = 0; i < x; i++) {
        a[i][i] = 1;
    }

    for(int from = 0; from < x; from++) {
        for(int to = max(0LL, from - k); to <= min(x - 1, from + k); to++) {
            b[from][to] = 1;
        }
    }

    vector<vector<ll>> res = matexp(a,b,n-1);

    for(auto &x : res) {
        for(auto &y : x) {
            w = (w + MOD - y) % MOD;
        }
    }

    cout << w << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}