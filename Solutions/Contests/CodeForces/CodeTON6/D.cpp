#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    ll low = LLONG_MAX;
    map<int,ll> m; //index, v[i]
    for(int i = n - 1; i >= 0; i--) {
        if(v[i] < low) {
            m[i] = v[i];
            low = v[i];
        }
    }
    ll coin; cin >> coin;

    vector<pair<ll,ll>> yikes(0);
    pair<int,ll> firstp = *m.begin();
    yikes.push_back({coin / firstp.second, firstp.first});
    coin -= coin / firstp.second * firstp.second;

    for(auto x = ++m.begin(); x != m.end(); x++) {
        ll costdiff = (*x).second - (*--x).second;
        x++;
        ll moves = min(coin / costdiff,yikes[yikes.size()-1].first);
        yikes[yikes.size()-1].first -= moves;
        yikes.push_back({moves,(*x).first});
        coin -= moves * costdiff;
    }

    vector<ll> ans(n);
    ll curr = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(yikes.size() && yikes[yikes.size()-1].second >= i) {
            curr += yikes[yikes.size()-1].first;
            yikes.pop_back();
        }
        ans[i] = curr;
    }
    for(auto x : ans) cout << x << " ";
    cout << "\n";
    // ll cost = (*m.begin()).second;
    // ll idx1 = (*m.begin()).first;
    // ll idx2 = idx1;
    // ll ops = coin / cost;
    // ll remainder = coin - ops * cost;
    // for(auto x = m.begin(); x != m.end(); x++) {
    //     if((*x).second - cost <= remainder) {
    //         // cout << "huh: " << (*x).second << " " << cost << " " << remainder << " ";
    //         idx2 = (*x).first;

    //     } else {
    //         break;
    //     }
    // }
    // // cout << "idx1: " << idx1 << " idx2: " << idx2 << "\n";
    // for(int i = 0; i < n; i++) {
    //     if(i > idx2) {
    //         cout << "0 ";
    //     } else if(i > idx1) {
    //         cout << 1 << " ";
    //     } else {
    //         cout << ops << " ";
    //     }
    // }
    // cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}