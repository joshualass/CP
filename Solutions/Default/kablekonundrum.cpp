#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    vector<ll> v(m);
    for(ll i = 0; i < n; i++) {
        ll room, search; cin >> room >> search;
        v[--room]+= search;
    }
    sort(v.begin(),v.end());
    ll N = 0;
    while(((N+1) << 1) <= m) {
        N++;
    }
    ll higher_count = (m - (N << 1))*2;
    ll lower_count = m - higher_count;
    // cout << lower_count << " " << higher_count << " " << N;
    ll count = 0;
    for(ll i = 0; i < higher_count; i++) {
        count += v[i] * (N + 1);
    }
    for(ll i = 0; i < lower_count; i++) {
        count += v[m-i-1] * N;
    }
    cout << count << "\n";

    return 0;
}