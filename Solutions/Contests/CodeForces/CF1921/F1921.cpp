#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int DIV = sqrt(1e5);

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    map<int,vector<array<int,3>>> queries;
    for(int i = 0; i < q; i++) {
        int s,d,k; cin >> s >> d >> k;
        if(queries.find(d) == queries.end()) {
            queries[d] = {};
        }
        queries[d].push_back({--s,k,i});
    }
    vector<ll> ans(n);
    vector<ll> prefs1(n);
    vector<ll> prefs2(n);
    for(pair<int,vector<array<int,3>>> qs : queries) {
        if(qs.first < DIV) {
            for(int i = 0; i < n; i++) {
                prefs1[i] = v[i];
                if(i - qs.first >= 0) {
                    prefs1[i] += prefs1[i - qs.first];
                }
                prefs2[i] = v[i] * (1 + i / qs.first);
                if(i - qs.first >= 0) {
                    prefs2[i] += prefs2[i - qs.first];
                }
            }
            for(array<int,3> query : qs.second) {
                // ans[query[2]] = prefs1[query[0] + query[1] * (qs.first - 1)];
                // if(query[0] - qs.first >= 0) {
                //     ans[query[2]] -= prefs1[query[0] - qs.first];
                // }
                
            }
        } else {
            for(array<int,3> query : qs.second) {
                ll cnt = 0;
                for(int i = 0; i < query[1]; i++) {
                    cnt += v[query[0] + i * qs.first] * (i + 1);
                }
                ans[query[2]] = cnt;
            }
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << " \n"[i == q - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}