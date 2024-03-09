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
void solve() {

    ll n; cin >> n;
    ll ans = 0;
    vector<pair<ll,pair<ll,ll>>> r = {{n,{1,1}}}; //size of the subtree, [left range of elements, right range of elements]
    while(r.size()) {
        vector<pair<ll,pair<ll,ll>>> nr;
        for(pair<ll,pair<ll,ll>> p : r) {
            ll s = p.first;
            ll ts = (p.second.first + p.second.second) % MOD * modInverse(2) % MOD * (p.second.second - p.second.first + 1) % MOD;
            // cout << "inf : " << p << '\n';
            if(s == 1) {
                ans += ts;
                ans %= MOD;
                // cout << "p : " << p << " addts : " << ts << '\n';
            } else {
                //the entire time, thought that the segtree was constructed in a different manner
                ll bs = 1;
                while(bs * 4 <= s) bs <<= 1;
                ll la = min(bs,s - bs * 2);
                ll ls = bs + la;
                ll rs = s - ls;
                // ll ls = (s + 1) / 2;
                // ll rs = s - ls;
                ll lm = binexp(2,ls) - 1;
                ll rm = binexp(2,rs) - 1; 
                ans += lm * rm % MOD * ts % MOD;
                // cout << "p : " << p << " ls : " << ls << " rs : " << rs << " add : " << lm * rm % MOD * ts % MOD << '\n';
                ans %= MOD;
                // nr.push_back({ls,{p.second.first,p.second.first+ls-1}});
                // nr.push_back({rs,{p.second.first+ls,p.second.second}});
                if(ls != rs) {
                    nr.push_back({ls,{p.second.first * 2, p.second.first * 2}});
                    nr.push_back({rs,{(p.second.first * 2 + 1), (p.second.first * 2 + 1)}});
                } else {
                    // cout << "s : " << s << " ls : " << ls << '\n';
                    nr.push_back({ls, {p.second.first * 2, (p.second.second * 2 + 1)}});
                }
                // nr.push_back({ls,{p.second.first * 2 % MOD, (p.second.first * 2 + ls - 1) % MOD}});
                // nr.push_back({rs,{(p.second.first * 2 + ls) % MOD, (p.second.first * 2 + s - 1) % MOD}});
            }
        }
        swap(r,nr);
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}