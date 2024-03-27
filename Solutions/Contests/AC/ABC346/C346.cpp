#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num <= k) s.insert(num);
    }
    ll ss = 0;
    for(int x : s) {
        ss += x;
    }
    cout << k * (k + 1) / 2 - ss << '\n';
    return 0;
}