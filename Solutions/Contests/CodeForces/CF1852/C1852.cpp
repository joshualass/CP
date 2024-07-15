#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//used editorial to solve
//set up everything correctly, but couldn't figure out how to determine for adjacent elements, which elements to decrease to match the other element
//we use a greedy approach, where we always try to descend, and if we can't descend, change previous descent to ascent
//equivalent is trying to always take the right side if possible and if not, see if it's better 

// no

void solve() {

    ll n, k; cin >> n >> k;

    ll res = 0;
    ll prev = 0;
    priority_queue<ll, vector<ll>, greater<ll>> lefts;

    for(int i = 0; i < n; i++) {
        ll next; cin >> next;
        next %= k;

        if(next == prev) continue;

        if(next > prev) {
            lefts.push(next - prev);
            res += lefts.top();
            lefts.pop();
        } else {
            lefts.push(next - prev + k);
        }
        prev = next;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}