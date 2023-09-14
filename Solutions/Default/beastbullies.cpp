#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int safe = 0;
    ll group = 0;
    ll count = 0;
    vector<ll> v(n);
    for(ll& x : v) cin >> x;
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    for(int i = 0 ; i < n; i++) {
        count += v[i];
        if(count >= group) {
            safe = i + 1;
            group += count;
            count = 0;
        }
    }
    cout << safe;

    return 0;
}