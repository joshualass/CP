#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

/*
conditions are not met and we do not like tedious hasing problems :(

*/

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

vector<vector<ll>> B = {
        {9337, 9817},
        {9001, 9547}
    };
vector<ll> M = {952388581, 941370203};

ll binexp(ll base, ll power, ll mod) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << "B" << endl;
    // for(auto x : B) cout << x;
    // cout << "M : " << M << endl;
    ll hp, wp, hm, wm; cin >> hp >> wp >> hm >> wm;

    vector<string> palling(hp);
    for(auto &x : palling) cin >> x;
    vector<string> m(hm);
    for(auto &x : m) cin >> x;

    auto pall = [&](vector<string> grid) -> vector<vector<array<ll,2>>> {
        ll n = sz(grid), m = sz(grid[0]);
        vector<vector<array<ll,2>>> a(n, vector<array<ll,2>>(m));
        vector<ll> rm(2, 1);
        for(ll i = 0; i < n; i++) {
            vector<ll> cm(2, 1);
            for(ll j = 0; j < m; j++) {
                if(grid[i][j] == 'o') {
                    array<ll,2> val = {};
                    for(int k = 0; k < 2; k++) {
                        val[k] = rm[k] * cm[k] % M[k];
                    }
                    a[i][j] = val;
                }
                for(int k = 0; k < 2; k++) {
                    cm[k] = cm[k] * B[1][k] % M[k];
                }
            }
            for(int j = 0; j < 2; j++) {
                rm[j] = (rm[j] * B[0][j]) % M[j];
            }
        }

        // cout << "a" << endl;
        // for(auto x : a) cout << x << endl;

        vector<vector<array<ll,2>>> p(n + 1, vector<array<ll,2>>(m + 1));
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                for(int k = 0; k < 2; k++) {
                    ll s = a[i][j][k] + p[i+1][j][k] + p[i][j+1][k] - p[i][j][k];
                    p[i+1][j+1][k] = ((s % M[k]) + M[k]) % M[k];
                }
            }
        }
        return p;
    };

    auto pp = pall(palling);
    auto p = pall(m);

    // cout << "pp" << endl;
    // for(auto x : pp) cout << x << endl;

    // cout << "p" << endl;
    // for(auto x : p) cout << x << endl;    

    auto good = pp[hp][wp];
    int res = 0;

    vector<vector<vector<ll>>> invs(2, vector<vector<ll>>(2, vector<ll>(2500)));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2500; k++) {
                if(k == 0) {
                    invs[i][j][k] = 1;
                } else if(k == 1) {
                    invs[i][j][k] = binexp(B[i][j], M[j] - 2, M[j]);
                } else {
                    invs[i][j][k] = invs[i][j][k-1] * invs[i][j][1] % M[j];
                }
            }
        }
    }

    for(ll i = hp; i <= hm; i++) {
        for(ll j = wp; j <= wm; j++) {
            array<ll,2> test = {};
            for(int k = 0; k < 2; k++) {
                test[k] = ((p[i][j][k] - p[i - hp][j][k] - p[i][j - wp][k] + p[i - hp][j - wp][k]) % M[k] + M[k]) % M[k];
            }
            // cout << "i : " << i << " j : " << j << " test part : " << test << endl;
            for(int k = 0; k < 2; k++) {
                test[k] = (test[k] * invs[0][k][i - hp]) % M[k];
                test[k] = (test[k] * invs[1][k][j - wp]) % M[k];
            }
            // cout << "i : " << i << " j : " << j << " test : " << test << endl;
            if(good == test) {
                // cout << "good for i : " << i << " j : " << j << endl;
                res++;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
