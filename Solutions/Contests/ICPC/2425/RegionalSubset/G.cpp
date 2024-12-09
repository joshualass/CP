#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<ll, ll>;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<pi> a(n);
    for (auto& p : a)
        cin >> p.first >> p.second;

    ll mxi = 0;
    ll mx = 0;

    for (ll i = 0; i < n; ++i) {
        if (a[i].second > mx) {
            mx = a[i].second;
            mxi = i;
        }
    }

    vector<pi> slopes(n);

    for (ll i = 0; i < n; ++i) {
        ll rise = abs(mx - a[i].second);
        ll run = abs(a[mxi].first - a[i].first);
        slopes[i] = {rise, run};
        
    }
    
    // cerr << "slopes\n";
    // for (auto x : slopes)
    //     cerr << x << " ";
    // cerr << endl;

    ll best_left = 0;
    ll lowest_left = 1e9;
    pi mn_slope = {0, 0};
    
    for (ll i = mxi-1; i > -1; --i) {
        if (slopes[i].first * mn_slope.second <= slopes[i].second * mn_slope.first) {

            if (a[i].second <= lowest_left) {
                best_left = i;
                lowest_left = a[i].second;
            }
            
            mn_slope = slopes[i];
        }
    }

    ll best_right = 0;
    ll lowest_right = 1e9;
    mn_slope = {0, 0};
    
    for (ll i = mxi+1; i < n; ++i) {
        if (slopes[i].first * mn_slope.second <= slopes[i].second * mn_slope.first) {
            if (a[i].second <= lowest_right) {
                best_right = i;
                lowest_right = a[i].second;
            }
            
            mn_slope = slopes[i];
        }
    }

    cout << a[best_left].first << " " << a[best_left].second << endl;
    cout << a[best_right].first << " " << a[best_right].second << endl;
       
    return 0;
}