#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, c; cin >> n >> c;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    sort(a.rbegin(), a.rend());
    for(int i = 0; i < n / 2; i++) {
        if(a.back() < c) a.pop_back();
    }

    cout << accumulate(a.begin(), a.end(), 0LL) - c * sz(a) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}