#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct sort_second {
    bool operator()(const pair<ll,ll> &left, const pair<ll,ll> &right) {
        if(left.second == right.second) {
            return left.first < right.first;
        } else {
            return left.second < right.second;
        }
    }
};

void solve() {
    ll n, p; cin >> n >> p;
    vector<pair<ll,ll>> v(n);
    for(auto &x: v) cin >> x.first;
    for(auto &x: v) cin >> x.second;
    sort(v.begin(),v.end(),sort_second());
    ll cost = p;
    int moves = 1;
    for(int i = 0; i < n; i++) {
        if(moves + v[i].first >= n) {
            cost += (n - moves) * min(v[i].second,p);
            break;
        } else {
            cost += v[i].first * min(v[i].second,p);
            moves += v[i].first;
        }
    }
    cout << cost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}