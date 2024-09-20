// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// int cnt_cycles(vector<int> &a) {
//     int cnt = 0;
//     vector<int> vis(a.size());

//     for(int i = 0; i < a.size(); i++) {
//         if(vis[i] == 0) {
//             queue<int> q;
//             q.push(i);
//             while(q.size()) {
//                 int b = q.front();
//                 q.pop();
//                 if(vis[b]) continue;
//                 vis[b] = 1;
//                 q.push(a[b]);
//             }
//             cnt++;
//         }
//     }
//     // cout << "a : " << a << " cnt : " << cnt << '\n';
//     return cnt;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     cout << "gimme n : " << endl;
//     int n; cin >> n;
//     vector<int> a(n);
//     iota(a.begin(), a.end(), 0);
//     ll cycles = n, cnt = 1;
//     while(next_permutation(a.begin(), a.end())) {
//         cnt++;
//         cycles += cnt_cycles(a);
//     }

//     cout << "cnt : " << cnt << " cycles : " << cycles << " expected : " << (((ld) cycles) / cnt) << '\n';

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

vector<ll> fact(1,1);
vector<ll> inv_fact(1,1);

ll choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size() % MOD);
        inv_fact.push_back(modInverse(fact.back(), MOD));
    }

    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "gimme n :" << flush;
    ll n;
    cin >> n;

    ll cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += choose(n,i) * fact[n-i] * fact[i-1];
        cout << "i : " << i << " adding : " << choose(n,i) * fact[n-i] * fact[i-1] << '\n';
    }

    cout << "Final cnt : " << cnt << '\n';

    return 0;
}