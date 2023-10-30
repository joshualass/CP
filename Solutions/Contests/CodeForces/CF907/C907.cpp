#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    sort(v.begin(), v.end());


    ll currx = 0;

    ll ans = 0;
    int i = 0;
    int back = n - 1;
    for( ; i < back; i++) {

        //can we use all first attacks on monster?

        if(v[back] >= currx + v[i]) {
            // cout << "action1\n";
            ans += v[i];
            currx += v[i];

        } else {
            // cout << "action2\n";
            ll attacks = v[back] - currx;
            v[i--] -= attacks;
            ans += attacks;
            currx += attacks;
        }

        //kill last monster
        if(currx == v[back]) {
            // cout << "action3\n";
            ans++;
            back--;
            currx = 0;
        }
    }

    // cout << "i: " << i << " back: " << back << " ans: " << ans << " currx: " << currx << '\n';

    if(i == back) {
        if(v[back] == 1) {
            ans--;
        }

        ans += 1 + ((v[back] + 1 - currx) / 2);
    }

    cout << ans << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}