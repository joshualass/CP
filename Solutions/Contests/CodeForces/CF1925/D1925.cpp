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

ll inverse(ll b) {
    return binexp(b,MOD-2);
}

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b) {
    return binexp(b,MOD-2) * a % MOD;
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    ll start = 0;
    for(int i = 0; i < m; i++) {
        ll a, b, f; cin >> a >> b >> f;
        start += f;
    }
    //total number of possible pairs to be selected
    ll num_pairs = n * (n - 1) / 2 % MOD;
    //expected initial value of all pairs
    ll pair_initial = modDivide(start % MOD, num_pairs);
    //factor to multiply each iteration
    ll mult = modDivide(num_pairs - 1, num_pairs);
    
    ll ans = pair_initial * k % MOD;
    cout << "ans start : " << ans << '\n';
    ll left = m;
    for(int excursion = 1; excursion <= k; excursion++) {
        //update left cnt
        ll new_left = left * mult % MOD;
        ll left_diff = (left - new_left + MOD) % MOD;
        left = new_left;
        cout << "left diff : " << left_diff << '\n';
        //find how many more excursions to choose from, the average, and the chance that this pair is selected again
        ll after_cnt = k - excursion; //rounds after 
        ll avg_score = modDivide(after_cnt + 1,2);
        ll choose_prob = modDivide(1,num_pairs);
        // cout << "excursion : " << excursion << " after cnt : " << after_cnt << " left_diff : " << left_diff << " choose_prob : " << choose_prob << " avg score: " << avg_score << '\n';
        ll val = after_cnt * avg_score % MOD * choose_prob % MOD * left_diff % MOD;
        // cout << "add val : " << val << '\n';
        ans += val;
        ans %= MOD;
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