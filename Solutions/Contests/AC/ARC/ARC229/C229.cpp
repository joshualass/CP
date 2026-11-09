#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    ll first = a.back();
    a.pop_back();
    ll last = a.back();
    a.pop_back();

    vector<vector<ll>> b(2);
    for(ll x : a) {
        b[x & 1].push_back(x);
    }

    vector<ll> res(1, first);
    for(int i = 0; i + 2 < n; i++) {
        int who;
        int prefer = (res.back() & 1) ^ 1;
        if(sz(b[prefer])) {
            who = prefer;
        } else {
            who = prefer ^ 1;
        }
        res.push_back(b[who].back());
        b[who].pop_back();
    }
    res.push_back(last);

    ll score = 0;
    for(int i = 0; i < n - 1; i++) {
        score += (res[i] + res[i+1]) / 2;
    }

    cout << score << '\n';

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