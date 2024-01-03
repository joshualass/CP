#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    ll sum = reduce(v.begin(), v.end());
    ll most = *max_element(v.begin(), v.end());

    if(most / 2 >= sum - most) {
        ll not_most = sum - most;
        cout << not_most << '\n';
    } else {
        cout << sum / 3 << '\n';
    }

    return 0;
}