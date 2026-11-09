#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    
    int cnt = count(a.begin(), a.end(), 1LL);
    if(cnt == n) {
        cout << "-1\n";
    } else {
        int loss;
        if((cnt == n - 1 && (a.front() != 1 || a.back() != 1)) || cnt == n - 2 && a.front() != 1 && a.back() != 1) {
            loss = n - 1;
        } else {
            loss = 1;
        }
        cout << accumulate(a.begin(), a.end(), 0LL) - loss << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}