#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll d;
    cin >> d;
    ll cash = 100;
    ll prev = 0;
    bool holding = false;
    bool first = true;
    ll shares = 0;
    ll lastbuy = 0;

    for (ll i = 0; i < d; i++) {
        ll p;
        cin >> p;
        if (first) {
            first = false;
        } else {
            if (holding) {
                if (p < prev) {  // sell sell sell
                    cash += shares * prev;
                    holding = false;
                    shares = 0;
                    // cout << "selling at price: " << prev << '\n';
                }
            } else {
                if (p > prev && prev <= cash) {  // buy max as possible
                    holding = true;
                    ll buys = min((ll)100000, cash / prev);
                    shares += buys;
                    cash -= buys * prev;
                    lastbuy = prev;
                    // cout << "buying at price: " << prev << '\n';
                }
            }
        }
        prev = p;
    }
    cout << cash + shares * max(prev,lastbuy);

    return 0;
}