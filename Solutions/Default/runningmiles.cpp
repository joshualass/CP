#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll SIZE = 1e5;
ll pref[SIZE], suff[SIZE], values[SIZE];
ll prefMax[SIZE], suffMax[SIZE];

void solve() {
    ll n; cin >> n;
    for(ll i = 0; i < n; i++) {
        ll num; cin >> num;
        pref[i] = i + num - n;
        // suff[i] = num - (n - i);
        suff[i] = num + n - i;
        values[i] = num;
    }
    prefMax[0] = pref[0];
    suffMax[n-1] = suff[n-1];
    for(ll i = 1; i < n; i++) {
        prefMax[i] = max(pref[i],prefMax[i-1]);
        suffMax[n-i-1] = max(suff[n-i-1],suffMax[n-i]);
    }
    ll most = -1;
    for(ll i = 1; i < n - 1; i++) {
        most = max(most, values[i] + prefMax[i-1] + suffMax[i+1]);
    }
    cout << most << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) {
        solve();
    }
    return 0;
}