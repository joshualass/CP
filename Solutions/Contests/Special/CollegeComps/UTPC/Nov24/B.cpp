#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> s(n), c(n);
    for(ll &x : s) cin >> x;
    for(ll &x : c) cin >> x;

    ll firstbad = INT_MAX, lastbad = INT_MIN;
    ll cur = 0;

    for(ll i = 0; i < n; i++) {
        cur += s[i];
        cur -= c[i];
        if(cur < 0) {
            firstbad = min(firstbad,i);
            lastbad = max(lastbad,i);
        }
    }

    if(firstbad == INT_MAX) {
        cout << "Yes\n";
        return 0;
    }

    ll loidx = 0;
    for(int i = 0; i <= firstbad; i++) {
        if(s[i] < s[loidx]) {
            loidx = i;
        }
    }

    ll hiidx = lastbad + 1;
    if(hiidx == n) {
        cout << "No\n";
        return 0;
    }

    for(int i = lastbad + 2; i < n; i++) {
        if(s[i] > s[hiidx]) {
            hiidx = i;
        }
    }

    swap(s[loidx], s[hiidx]);
    cur = 0;
    
    for(int i = 0; i < n; i++) {
        cur += s[i];
        cur -= c[i];
        if(cur < 0) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";

    return 0;
}