#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {

        int n, m; cin >> n >> m;
        vector<ll> v(m); //sticker count
        vector<vector<ll>> prizes(n,vector<ll>(0));
        vector<ll> values(n);
        for(ll i = 0; i < n; i++) {
            ll stickers; cin >> stickers;
            for(ll l = 0; l < stickers; l++) {
                ll num; cin >> num;
                prizes[i].push_back(num);
            }
            cin >> values[i];
        }
        for(ll &x : v) cin >> x;
        ll cash = 0;
        for(ll i = 0; i < n; i++) {
            ll least = INT_MAX;
            for(ll l = 0; l < prizes[i].size(); l++) {
                least = min(least, v[prizes[i][l]-1]);
            }
            cash += values[i] * least;
        }
        cout << cash << '\n';
    }

    return 0;
}