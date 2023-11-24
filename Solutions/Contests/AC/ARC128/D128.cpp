//still not correct
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll binexp(ll base, ll power, ll MOD = 998244353) {
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

ll modDivide(ll a, ll b, ll MOD = 998244353) {
    return binexp(b,MOD-2,MOD) * a % MOD;
}

ll get_dp(ll curr) {
    vector<array<ll,2>> dp(curr);
    dp[0][0] = 1;
    dp[0][1] = 1;
    for(int i = 1; i < curr; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][1] = (dp[i-1][0] + dp[i-1][1]) % MOD;
    }

    ll sum = (dp.back()[0] + dp.back()[1]) % MOD;
    ll div = binexp(2, curr);
    ll ans = modDivide(sum,div);
    // cout << "num : " << sum << " div : " << div << '\n';
    // cout << "dp - curr : " << curr << " ans : " << ans << '\n';

    // return ans;
    // return sum;
    return (div - sum + MOD) % MOD;
}

ll solve(vector<ll> v) {
    if(v.size() <= 2) return 1;//no operations ever possible on short length

    ll start_ops = binexp(2, v.size() - 2);
    int curr = 0;
    ll remove = 0;
    v.push_back(-1);
    for(int i = 2; i < v.size(); i++) {
        if(v[i] == v[i-2]) {
            curr++;
        } else {
            if(curr >= 1) {
                // start_ops *= get_dp(curr);
                // start_ops %= MOD;
                ll unreachable = get_dp(curr);
                // cout << "curr : " << curr << " get_dp(curr) : " << unreachable << '\n';
                if(remove == 0) {
                    remove = unreachable;
                } else {
                    remove = remove * unreachable % MOD;
                }
            }
            curr = 0;
        }
    }
    
    // cout << "v : " << v << '\n' << "ans : " << (start_ops + MOD - remove) % MOD << '\n';
    return (start_ops + MOD - remove) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);

    for(auto &x: v) cin >> x;
    v.push_back(v.back());
    vector<ll> cur;
    int prev = -1;
    ll ans = 1;
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == prev) {
            
            // cur.push_back(v[i]);
            ans *= solve(cur);
            ans %= MOD;
            cur.clear();
        }
        cur.push_back(v[i]);
        prev = v[i];
    }
    cout << ans << '\n';

    return 0;
}