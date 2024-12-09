#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool is_valid(int d, ld pd, ld pe, ld pi, int x){
    int mod = 7;
    int cur = d - x;
    while(cur < 0){
        cur += mod;
    }
    ld p = 1;
    for(int i = 0; i < x; i++){
        // cout << "CUR : " << cur << "\n";
        if(cur == 0 || cur == 6){
            p *= (1.0 - pe);
        }
        else {
            p *= (1.0 - pd);
        }
        cur = (cur + 1) % mod;
    }
    return (1.0 - p) >= pi;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d;
    cin >> d;
    d --;
    ld pd, pe;
    cin >> pd >> pe;
    pd /= 100.0;
    pe /= 100.0;
    ld pi;
    cin >> pi;
    pi /= 100.0;
    int low = 1;
    int high = 1e6;
    int ans = high;
    while(low <= high){
        int mid = low + (high - low) / 2;
        if(is_valid(d, pd, pe, pi, mid)) {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    int l = d - ans;
    while(l < 0){
        l += 7;
    }
    vector<string> s = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    cout << "Try to leave on " << s[l] << ", " << ans << " day" << (ans == 1? "" : "s") << " before the " << s[d] << " meeting.\n";
    // cout << ans << "\n";

    return 0;
}