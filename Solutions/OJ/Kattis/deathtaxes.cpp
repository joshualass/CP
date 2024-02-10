#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll shares = 0;
    ld pps = 0;
    string cmd; 
    cin >> cmd;

    while(!cin.eof()) {
        if(cmd == "buy") {
            ll x, y; cin >> x >> y;
            pps = (pps * shares + x * y) / (shares + x);
            shares += x;
        }
        if(cmd == "sell") {
            ll x, y; cin >> x >> y;
            shares -= x;
        }
        if(cmd == "split") {
            ll x; cin >> x;
            shares *= x;
            pps /= x;
        }
        if(cmd == "merge") {
            ll x; cin >> x;
            shares /= x;
            pps *= x;
        }
        if(cmd == "die") {
            ll y; cin >> y;
            ld profit = y - pps;
            profit = max(profit * 0.3, (ld)0);
            cout << fixed << setprecision(5) << shares * (y - profit) << '\n';
        }
        cin >> cmd;
    }

    return 0;
}