#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m = MOD) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
 
ll modDivide(ll a, ll b) {
    a = a % MOD;
    int inv = modInverse(b, MOD);
    return (inv * a) % MOD;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

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

//L bozo has to debug 
//lower your tone before talking with the king.
void solve() {

    ll n; cin >> n;
    vector<vector<ll>> v = {{n,1,1}}; // subtree size, sigma value, quantity
    ll ans = 0;
    while(v.size()) {
        map<ll,vector<vector<ll>>> m;
        for(vector<ll> a : v) {
            // cout << "a {" << a[0] << ", " << a[1] << ", " << a[2] << "}\n";
            if(a[0] == 1) {
                ans += a[1];
                ans %= MOD;
                continue;
            }
            ll ls = (a[0] + 1) / 2;
            ll rs = a[0] / 2;
            ll lm = binexp(2,ls) - 1;
            ll rm = binexp(2,rs) - 1;
            ans += lm * rm % MOD * a[1] % MOD;
            ans %= MOD;
            // cout << "lm : " << lm << " rm : " << rm << " a[1] " << a[1] << '\n';
            // cout << "add : " << lm * rm % MOD * a[1] % MOD << '\n';
            if(ls == rs) {
                // if(nv.size() && nv.back()[0] == ls) {
                //     nv.back()[1]  = (nv.back()[1] + a[1] * 4 + a[2]) % MOD;
                //     nv.back()[2] = (nv.back()[2] + a[2] * 2) % MOD;
                // } else {
                //     nv.push_back({ls, (a[1] * 4 + a[2]) % MOD, a[2] * 2 % MOD});
                // }
                m[ls].push_back({(a[1] * 4 + a[2]) % MOD, a[2] * 2 % MOD});
            } else {
                // nv.push_back({ls, (a[1] * 2) % MOD, a[2]});
                // nv.push_back({rs, (a[1] * 2 + a[2]) % MOD, a[2]});
                m[ls].push_back({(a[1] * 2) % MOD, a[2]});
                m[rs].push_back({(a[1] * 2 + a[2]) % MOD, a[2]});
            }
        }
        v.clear();
        for(auto [u, nv] : m) {
            v.push_back({u,0,0});
            for(vector<ll> a : nv) {
                v.back()[1] = (v.back()[1] + a[0]) % MOD;
                v.back()[2] = (v.back()[2] + a[1]) % MOD;
            }
        }
    }
    cout << ans << '\n';
    // ll n; cin >> n;
    // vector<vector<ll>> v = {{n,1,1,1}};
    // ll ans = 0;
    // while(v.size()) {
    //     vector<vector<ll>> nv;
    //     for(vector<ll> a : v) {
    //         cout << "a {" << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << "}\n";
    //         if(a[0] == 1) {
    //             ll ts = (a[1] * a[3] + a[2] * a[3] % MOD * (a[3] - 1) % MOD * modInverse(2)) % MOD;
    //             ans += ts;
    //             cout << "add : " << ts << '\n';
    //             ans %= MOD;
    //             continue;
    //         }
    //         ll ls = (a[0] + 1) / 2;
    //         ll rs = a[0] / 2;
    //         ll lm = binexp(2,ls) - 1;
    //         ll rm = binexp(2,rs) - 1;
    //         ll ts = (a[1] * a[3] + a[2] * a[3] % MOD * (a[3] - 1) % MOD * modInverse(2)) % MOD;
    //         ans += lm * rm % MOD * ts % MOD;
    //         cout << "add : " << lm * rm % MOD * ts % MOD << '\n';
    //         ans %= MOD;
    //         if(ls == rs) {
    //             nv.push_back({ls, a[1] * 2, a[2], a[3] * 2});
    //         } else {
    //             nv.push_back({ls, a[1] * 2, a[2] * 2, a[3]});
    //             nv.push_back({rs, a[1] * 2 + 1, a[2] * 2, a[3]});
    //         }
    //     }
    //     swap(v,nv);
    // }
    // cout << ans << '\n';
    // ll n; cin >> n;
    // ll ans = 0;
    // vector<pair<ll,pair<ll,ll>>> r = {{n,{1,1}}}; //size of the subtree, [left range of elements, right range of elements]
    // while(r.size()) {
    //     vector<pair<ll,pair<ll,ll>>> nr;
    //     for(pair<ll,pair<ll,ll>> p : r) {
    //         ll s = p.first;
    //         ll ts = (p.second.first + p.second.second) % MOD * modInverse(2) % MOD * (p.second.second - p.second.first + 1) % MOD;
    //         // cout << "inf : " << p << '\n';
    //         if(s == 1) {
    //             ans += ts;
    //             ans %= MOD;
    //             // cout << "p : " << p << " addts : " << ts << '\n';
    //         } else {
    //             //the entire time, thought that the segtree was constructed in a different manner
    //             ll bs = 1;
    //             while(bs * 4 <= s) bs <<= 1;
    //             ll la = min(bs,s - bs * 2);
    //             ll ls = bs + la;
    //             ll rs = s - ls;
    //             // ll ls = (s + 1) / 2;
    //             // ll rs = s - ls;
    //             ll lm = binexp(2,ls) - 1;
    //             ll rm = binexp(2,rs) - 1; 
    //             ans += lm * rm % MOD * ts % MOD;
    //             // cout << "p : " << p << " ls : " << ls << " rs : " << rs << " add : " << lm * rm % MOD * ts % MOD << '\n';
    //             ans %= MOD;
    //             // nr.push_back({ls,{p.second.first,p.second.first+ls-1}});
    //             // nr.push_back({rs,{p.second.first+ls,p.second.second}});
    //             if(ls != rs) {
    //                 nr.push_back({ls,{p.second.first * 2, p.second.first * 2}});
    //                 nr.push_back({rs,{(p.second.first * 2 + 1), (p.second.first * 2 + 1)}});
    //             } else {
    //                 // cout << "s : " << s << " ls : " << ls << '\n';
    //                 nr.push_back({ls, {p.second.first * 2, (p.second.second * 2 + 1)}});
    //             }
    //             // nr.push_back({ls,{p.second.first * 2 % MOD, (p.second.first * 2 + ls - 1) % MOD}});
    //             // nr.push_back({rs,{(p.second.first * 2 + ls) % MOD, (p.second.first * 2 + s - 1) % MOD}});
    //         }
    //     }
    //     swap(r,nr);
    // }
    // cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}