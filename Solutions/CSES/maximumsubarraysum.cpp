#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;

    ll most = LLONG_MIN;

    ll sum = 0;
    for(int i = 0; i < n; i++) {
        if(sum + v[i] < 0) {
            most = max(most, v[i]);
            sum = 0;
        } else {
            sum += v[i];
            most = max(sum, most);
        }
    }
    cout << most << "\n";
    return 0;
}
