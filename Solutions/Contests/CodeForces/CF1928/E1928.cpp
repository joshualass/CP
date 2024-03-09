#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

vector<pair<int,int>> min_tri;

void solve() {
    ll n, x, y, s; cin >> n >> x >> y >> s;
    s -= (x % y) * n;
    if(s % y != 0) {
        cout << "no\n";
        return;
    }
    vector<ll> ans;
    ll start = x / y;
    ll needed = s / y;
    ans.push_back(start);
    needed -= start;
    int found = -1;
    while(true) {
        if(needed < 0) break;
        if(min_tri[needed].first <= n - (int)ans.size()) {
            found = needed;
            break;
        }
        ans.push_back(ans.back() + 1);
        needed -= ans.back();
    }

    if(found == -1) {
        cout << "no\n";
        return;
    }
    // cout << "found : " << found << '\n';
    while(found != 0) {
        for(int i = 0; i <= min_tri[found].second; i++) {
            ans.push_back(i);
        }
        found -= min_tri[found].second * (min_tri[found].second + 1) / 2;
    }
    // cout << "ans ? : " << ans << '\n';
    if(ans.size() > n) {
        cout << "??\n";
        return;
    }
    while(ans.size() != n) ans.push_back(0);
    cout << "yes\n";
    for(int i = 0; i < n; i++) {
        cout << (x % y) + ans[i] * y << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    min_tri.assign(200001,{INT_MAX,INT_MAX});
    min_tri[0] = {0,0};
    for(int i = 1; i < 200001; i++) {
        for(int j = 1; i - j * (j + 1) / 2 >= 0; j++) {
            if(min_tri[i - j * (j + 1) / 2].first + j < min_tri[i].first) {
                min_tri[i] = {min_tri[i - j * (j + 1) / 2].first + j + 1,j};
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}