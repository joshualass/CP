#include <bits/stdc++.h>
typedef unsigned long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
sanity check that we don't visit enough states, number of visited states is bounded. 

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, x; cin >> n >> x;

    ll big = 1;
    for(int i = 1; i < n; i++) big *= 10;

    set<ll> s;
    queue<array<ll,2>> q;
    q.push({x, 0});
    while(sz(q)) {
        auto [x, ops] = q.front();
        q.pop();
        // cout << "x : " << x << " ops : " << ops << endl;
        ll t = x;
        while(t) {
            ll dig = t % 10;
            if(dig >= ((ld) big) / x) {
                cout << ops + 1 << '\n';
                return 0;
            }
            if(s.count(x * dig) == 0) {
                s.insert(x * dig);
                q.push({x * dig, ops + 1});
            }
            t /= 10;
        }
    }

    cout << "-1\n";

    return 0;
}
