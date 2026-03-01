#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    sort(a.begin(), a.end());
    vector<int> good_a(n + m + 1);
    for(ll x : a) {
        if(good_a[x] == 0) {
            for(int i = x; i <= n + m; i += x) good_a[i] = 1;
        }
    }
    ll bob_lcm = 1;
    for(ll x : a) {
        bob_lcm = min(10'000'000LL, x * bob_lcm / gcd(x, bob_lcm));
    }
    int alice = 0, bob = 0, ab = 0;
    for(ll x : b) {
        if(x % bob_lcm) {
            if(good_a[x]) {
                // cout << "x : " << x << " ab\n";
                ab++;
            } else {
                // cout << "x : " << x << " bob\n";
                bob++;
            }
        } else {
            if(good_a[x]) {
                // cout << "x : " << x << " alice\n";
                alice++;
            }
        }
    }

    if(ab & 1) alice++;

    // cout << "alice : " << alice << " ab : " << ab << " bob : " << bob << endl;

    cout << (alice > bob ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}