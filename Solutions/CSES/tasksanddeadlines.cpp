#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<ll,ll>> v(n);
    for(auto &x: v) cin >> x.first >> x.second;
    sort(v.begin(),v.end());
    ll sum = 0;
    ll time = 0;
    for(int i = 0; i < n; i++) {
        time += v[i].first;
        sum += v[i].second - time;
    }
    cout << sum << "\n";
    return 0;
}