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

// ll inverse(ll b) {
//     return binexp(b,MOD-2);
// }

// //returns a / b using modular inverse. this implementation uses fermat's little theorem
// ll modDivide(ll a, ll b) {
//     return binexp(b,MOD-2) * a % MOD;
// }

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

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

void solve() {

    ll n, m, k; cin >> n >> m >> k;
    ll pairs = n * (n - 1) / 2 % MOD;
    ll ans = 0;
    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c;
        ans = (ans + k * c % MOD * modInverse(pairs)) % MOD;
    }
    for(ll i = 0; i <= k; i++) {
        //probability that a friendship pair is chosen i times out of k
        ll c = choose(k,i);
        ll ph = modInverse(binexp(pairs,i));
        ll pm = binexp(pairs-1,k-i) * modInverse(binexp(pairs,k-i)) % MOD;
        ll add = i * (i - 1) / 2 % MOD * m % MOD * c % MOD * ph % MOD * pm % MOD;
        // cout << "i : " << i << " c : " << c << " ph : " << ph << " pm : " << pm << '\n';
        // cout << "i : " << i << " add : " << add << '\n';
        ans = (ans + add) % MOD;
    }
    cout << ans << '\n';
    //misread problem twice ... oops
    // ll n, m, k; cin >> n >> m >> k;
    // ll num_pairs = n * (n - 1) / 2 % MOD;
    // ll sumf = 0;
    // for(int i = 0; i < m; i++) {
    //     ll a, b, c; cin >> a >> b >> c;
    //     sumf += c;
    // }
    // sumf %= MOD;
    // ll avgf = sumf * modInverse(num_pairs) % MOD;
    // ll ans = 0; //cumulative sum
    // ll s = 0;  //total probability
    // ll ss = 0; //added to here each time
    // for(int e = 0; e < k; e++) {
    //     ss = (ss + s) % MOD;
    //     ans = (ans + ss * modInverse(num_pairs) + avgf) % MOD;
    //     ll p = m * modInverse(num_pairs) % MOD; //probability of hitting an unhit pair on this excursion
    //     // cout << "e : " << e << " p : " << p << '\n';
    //     s += p;
    //     m = (m - p + MOD) % MOD;
    //     // cout << "upd m : " << m << '\n';
    // }
    // cout << ans << '\n';
    //sad, not working, solution. 
    // ll n, m, k; cin >> n >> m >> k;
    // ll start = 0;
    // for(int i = 0; i < m; i++) {
    //     ll a, b, f; cin >> a >> b >> f;
    //     start += f;
    // }
    // //total number of possible pairs to be selected
    // ll num_pairs = n * (n - 1) / 2 % MOD;
    // //expected initial value of all pairs
    // ll pair_initial = modDivide(start % MOD, num_pairs);
    // //factor to multiply each iteration
    // ll mult = modDivide(num_pairs - 1, num_pairs);
    
    // ll ans = pair_initial * k % MOD;
    // cout << "ans start : " << ans << '\n';
    // ll left = m;
    // for(int excursion = 1; excursion <= k; excursion++) {
    //     //update left cnt
    //     ll new_left = left * mult % MOD;
    //     ll left_diff = (left - new_left + MOD) % MOD;
    //     left = new_left;
    //     cout << "left diff : " << left_diff << '\n';
    //     //find how many more excursions to choose from, the average, and the chance that this pair is selected again
    //     ll after_cnt = k - excursion; //rounds after 
    //     ll avg_score = modDivide(after_cnt + 1,2);
    //     ll choose_prob = modDivide(1,num_pairs);
    //     // cout << "excursion : " << excursion << " after cnt : " << after_cnt << " left_diff : " << left_diff << " choose_prob : " << choose_prob << " avg score: " << avg_score << '\n';
    //     ll val = after_cnt * avg_score % MOD * choose_prob % MOD * left_diff % MOD;
    //     // cout << "add val : " << val << '\n';
    //     ans += val;
    //     ans %= MOD;
    // }

    // cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    factorial();
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}