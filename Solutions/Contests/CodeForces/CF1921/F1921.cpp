#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int sq = sqrt(100000);

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    vector<vector<ll>> prefs(sq,vector<ll>(n));
    vector<vector<ll>> prefsk(sq,vector<ll>(n));
    for(int d = 1; d < sq; d++) {
        for(int i = 0; i < n; i++) {
            if(i - d >= 0) {
                prefs[d][i] = prefs[d][i-d];
                prefsk[d][i] = prefsk[d][i-d];
            }
            prefs[d][i] += v[i];
            prefsk[d][i] += v[i] * (1 + i / d);
        }
    }

    for(int i = 0; i < q; i++) {
        ll s, d, k; cin >> s >> d >> k;
        s--;
        if(d < sq) {
            ll ans = prefsk[d][s + d * (k - 1)] - prefs[d][s + d * (k - 1)] * (s / d);
            if(s - d >= 0) {
                ans -= prefsk[d][s-d] - prefs[d][s-d] * (s / d);
            } 
            cout << ans;
        } else {
            ll ans = 0;
            for(int i = 1; i <= k; i++) {
                ans += v[s + d * (i - 1)] * i;
            }
            cout << ans;
        }
        cout << " \n"[i == q - 1];
    }
}

// const int DIV = sqrt(1e5);

// void solve() {
//     int n, q; cin >> n >> q;
//     vector<ll> v(n);
//     for(ll &x : v) cin >> x;
//     map<int,vector<array<int,3>>> queries;
//     for(int i = 0; i < q; i++) {
//         int s,d,k; cin >> s >> d >> k;
//         if(queries.find(d) == queries.end()) {
//             queries[d] = {};
//         }
//         queries[d].push_back({--s,k,i});
//     }
//     vector<ll> ans(n);
//     vector<ll> prefs1(n);
//     vector<ll> prefs2(n);
//     for(pair<int,vector<array<int,3>>> qs : queries) {
//         if(qs.first < DIV) {
//             for(int i = 0; i < n; i++) {
//                 prefs1[i] = v[i];
//                 if(i - qs.first >= 0) {
//                     prefs1[i] += prefs1[i - qs.first];
//                 }
//                 prefs2[i] = v[i] * (1 + i / qs.first);
//                 if(i - qs.first >= 0) {
//                     prefs2[i] += prefs2[i - qs.first];
//                 }
//             }
//             for(array<int,3> query : qs.second) {
//                 // ans[query[2]] = prefs1[query[0] + query[1] * (qs.first - 1)];
//                 // if(query[0] - qs.first >= 0) {
//                 //     ans[query[2]] -= prefs1[query[0] - qs.first];
//                 // }
                
//             }
//         } else {
//             for(array<int,3> query : qs.second) {
//                 ll cnt = 0;
//                 for(int i = 0; i < query[1]; i++) {
//                     cnt += v[query[0] + i * qs.first] * (i + 1);
//                 }
//                 ans[query[2]] = cnt;
//             }
//         }
//     }
//     for(int i = 0; i < q; i++) {
//         cout << ans[i] << " \n"[i == q - 1];
//     }
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}