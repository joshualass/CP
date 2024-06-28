#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    int ascore = 0, bscore = 0;
    vector<int> e;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) {
            ascore += a[i];
        } else if(b[i] > a[i]) {
            bscore += b[i];
        } else {
            e.push_back(a[i]);
        }
    }
    for(int x : e) {
        if(abs(ascore + x - bscore) < abs(ascore - x - bscore)) {
            ascore += x;
        } else {
            bscore += x;
        }
    }
    cout << min(ascore, bscore) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}