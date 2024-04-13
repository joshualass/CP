#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;

    vector<pair<int,int>> v;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(v.empty() || num != v.back().first) {
            v.push_back({num,1});
        } else {
            v.back().second++;
        }
    }

    if(v.size() == 1) {
        cout << "-1\n";
        return;
    }

    // bool is_beautiful = 0;
    // if(v.front().first != v.back().first) is_beautiful = 1;
    // for(int i = 0; i < v.size(); i++) {
    //     if(v[i].first != v.front().first && v[i].second >= 2) is_beautiful = 1;
    // }

    int best = INT_MAX;
    for(int i = 0; i < v.size(); i++) {
        if(v[i].first == v[0].first) {
            best = min(best, v[i].second);
        }
    }    
    cout << best << '\n';
    // vector<int> v(n);
    // for(int &x : v) cin >> x;
    // int lm = 0, rm = 0;
    // for(int i = 0; i < n; i++) {
    //     if(v[i] != v.back()) {
    //         break;
    //     }
    //     lm = i + 1;
    // }
    // reverse(v.begin(), v.end());
    // for(int i = 0; i < n; i++) {
    //     if(v[i] != v.back()) {
    //         break;
    //     }
    //     rm = i + 1;
    // }
    // if(lm == n) {
    //     cout << "-1\n";
    // } else {
    //     cout << min(lm, rm) << '\n';
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}