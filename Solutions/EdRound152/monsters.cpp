#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
void solve() {
    ll n, k; cin >> n >> k;
    vector<pair<ll,ll>> v(n);
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        v[i] = {k - ((num-1) % k), i};
        
        // v[i] = {((num-1) % k)+1, i};
        // v[i] = {num % k - num, i};
        // if(k >= num) {
        //     v[i] = {-num, i};
        // } else {
        //     v[i] = {num % k, i};
        // }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++) {
        cout << ++v[i].second << " ";
    }
    cout << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
