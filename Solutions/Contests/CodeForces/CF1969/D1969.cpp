#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    vector<pair<ll,ll>> items;

    for(int i = 0; i < n; i++) {
        if(a[i] <= b[i]) {
            items.push_back({a[i],b[i]});
        }
    }

    sort(items.begin(), items.end());

    ll costa = 0;
    ll costb = 0;
    ll res = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    for(int i = 0; i < items.size(); i++) {
        costa += items[i].first;
        if(pq.size() < k) {
            pq.push(items[i].second);
        } else {
            if(pq.size() && items[i].second > pq.top()) {
                costb += pq.top();
                pq.pop();
                pq.push(items[i].second);
            } else {
                costb += items[i].second;
            }
        }
        res = max(res, costb - costa);
    }
    cout << res << '\n';
    // ll curra = 0;
    // ll currb = 0;

    // for(int i = 0; i < items.size(); i++) {
    //     curra += items[i].first;
    //     if(i < items.size() - k) {
    //         currb += items[i].second;
    //     }
    // }
    // ll res = 0;
    // for(int i = ((int)items.size()) - 1; i >= 0; i--) {
    //     res = max(res, currb - curra);
    //     curra -= items[i].first;
    //     if(i - k >= 0) {
    //         currb -= items[i-k].second;
    //     }
    // }   
    // cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}