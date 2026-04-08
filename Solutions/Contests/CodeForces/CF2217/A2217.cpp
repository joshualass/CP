#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    cout << (((n * accumulate(a.begin(), a.end(), 0)) & 1) || (k * n % 2 == 0) ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}