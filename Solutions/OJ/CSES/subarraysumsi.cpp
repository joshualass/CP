#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x; cin >> n >> x;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    ll curr = 0;
    int idx = 0;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        curr += v[i];
        while(curr > x) {
            curr -= v[idx++];
        }
        if(curr == x) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}