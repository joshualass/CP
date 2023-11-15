// https://open.kattis.com/problems/opportunity
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

array<ll,3> oc(vector<array<ll,3>> &v, bool x, bool y, bool z) {
    array<ll,3> ans = {0,0,0};

    for(int i = 0; i < v.size(); i++) {
        ll ansscore = 0;
        ll currscore = 0;
        if(x) {
            ansscore += ans[0];
            currscore += v[i][0];
        }
        if(y) {
            ansscore += ans[1];
            currscore += v[i][1];
        }
        if(z) {
            ansscore += ans[2];
            currscore += v[i][2];
        }
        if(currscore > ansscore) {
            ans = v[i];
        }
    }
    return ans;
}

//cost of b from phone a
ll calccost(array<ll,3> &a, array<ll,3> &b) {
    ll ans = 0;

    ans += max(0LL, a[0] - b[0]);
    ans += max(0LL, a[1] - b[1]);
    ans += max(0LL, a[2] - b[2]);

    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<array<ll,3>> v(n);
    for(auto &x: v) {
        for(auto &y: x) {
            cin >> y;
        }
    }

    pair<ll,ll> ans = {MOD * 3, 0};
    vector<array<ll,3>> compares;

    for(int i = 0; i < 8; i++) {
        compares.push_back(oc(v,i & 1, (i >> 1) & 1, (i >> 2) & 1));
    }

    for(int i = 0; i < n; i++) {
        ll num = 0;
        for(int j = 0; j < 8; j++) {
            num = max(num, calccost(compares[j], v[i]));
        }
        if(num < ans.first) {
            ans = {num, i};
        }
    }

    cout << ans.first << " " << ans.second + 1 << '\n';

    return 0;
}