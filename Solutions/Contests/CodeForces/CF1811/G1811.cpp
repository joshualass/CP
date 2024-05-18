#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1'000'000'007;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
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

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

void solve() {

    ll n, k; cin >> n >> k;
    vector<vector<ll>> cp(n);
    vector<ll> c(n);
    vector<ll> ci(n);
    vector<pair<ll,ll>> dp(n+1); //{num segments, num paths of that length}
    vector<pair<ll,ll>> dpm(n+1);

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        num--;
        c[i] = num;
        ci[i] = cp[num].size();
        cp[num].push_back(i);
    }
    if(k == 1) {
        cout << "1\n";
        return;
    }
    dpm[0] = {0,1};
    for(int i = 0; i < n; i++) {
        ll cm = 0;

        int col = c[i];
        
        for(int j = k - 1; j < k * 2 - 1 && ci[i] - j >= 0; j++) {
            // cout << "aqui\n";
            pair<ll,ll> p = dpm[cp[col][ci[i] - j]];
            p.first++; //increase length
            p.second = p.second * choose(j - 1, k - 2) % MOD;
            i++;
            if(p.first > dp[i].first) {
                dp[i] = p;
            } else if(p.first == dp[i].first) {
                dp[i].second = (p.second + dp[i].second) % MOD;
            }
            i--;
        }
        // cout << "i : " << i << " f : " << dp[i+1].first << " s : " << dp[i+1].second << '\n';
        for(int j = 1; j <= n; j++) {
            dpm[j] = dpm[j-1];
            if(dpm[j].first < dp[j].first) {
                dpm[j] = dp[j];
            } else if(dpm[j].first == dp[j].first) {
                // dpm[j].second += dp[j].second;
                dpm[j].second = (dpm[j].second + dp[j].second) % MOD;
            }
        }
    }
    cout << dpm.back().second << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}