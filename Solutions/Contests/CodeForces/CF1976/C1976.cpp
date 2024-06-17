#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

vector<ll> solver(vector<ll> &a, vector<ll> &b, int n, int m) {
    int ncnt = 0, mcnt = 0;
    vector<bool> takea(n+m);
    for(int i = 0; i < n + m; i++) {
         if(a[i] > b[i] && ncnt != n || mcnt == m) {
            takea[i] = 1;
            ncnt++;
         } else {
            mcnt++;
         }
    }
    vector<ll> scores(n+m+1);
    for(int i = n + m - 1; i >= 0; i--) {
        if(takea[i]) {
            scores[i] = a[i];
        } else {
            scores[i] = b[i];
        }
        scores[i] += scores[i+1];
    }
    return scores;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> a(n+m+1), b(n+m+1);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    vector<ll> ascores = solver(a,b,n+1,m);
    vector<ll> bscores = solver(a,b,n,m+1);


    ll res = 0, ncnt = 0, mcnt = 0;
    for(int i = 0; i < n + m + 1; i++) {
        cout << res + (a[i] > b[i] ? ascores[i+1] : bscores[i+1]) << " \n"[i == n + m];
        if(a[i] > b[i] && ncnt != n || mcnt == m) {
            res += a[i];
            ncnt++;
        } else {
            res += b[i];
            mcnt++;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}