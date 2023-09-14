#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll height(ll a, ll b, ll n) {
    return ((a-b)*(n-1) + a);
}

ll days(ll a, ll b, ll h) { //how many days given a and b to reach height h
    ll days = 1;
    h -= a;
    if(h <= 0) {
        return days;
    }
    days += h / (a - b);
    if(h % (a - b) != 0) {
        days++;
    }
    return days;
    // return (h - a) / (a - b) + (((h - a) % (a - b)) == 0 ? 0 : 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int q; cin >> q;
        ll l = 1;
        ll r = LLONG_MAX;
        for(int i = 0; i < q; i++) {
            int op; cin >> op;
            if(op == 1) {
                ll a, b, n; cin >> a >> b >> n;
                ll low = -1;
                ll high = -1;
                if(n == 1) {
                    high = a;
                    low = 1;
                } else {
                    high = height(a,b,n);
                    low = height(a,b,n-1) + 1;
                }
                if(low > r || high < l) {
                    cout << "0 ";
                    continue;
                }
                cout << "1 ";
                // cout << " old l: " << l << " old r: " << r << " new l: " << low << " new r: " << high << "\n"; 
                l = max(low,l);
                r = min(r,high);
                
            } else {
                ll a, b; cin >> a >> b;
                ll low = days(a,b,l);
                ll high = days(a,b,r);
                // cout << " old l: " << l << " old r: " << r << " query l: " << low << " query r: " << high << "\n"; 
                if(low == high) {
                    cout << low << " ";
                } else {
                    cout << "-1 ";
                }
            }
        }
        cout << "\n";
    }

    return 0;
}