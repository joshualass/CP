#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

map<pair<vector<ll>, int>, int> dp;

int dfs(vector<ll> a, int turn) {
    sort(a.begin(), a.end());
    // cout << "a : " << a << " turn : " << turn << endl;
    if(dp.count({a, turn}) == 0) {
        int f = 0;
        for(int i = 0; i < sz(a); i++) {
            for(int j = 1; j <= a[i]; j++) {
                auto c = a;
                c[i] -= j;
                int next = turn - 1;
                if(next == 0) {
                    f |= dfs(c, sz(a) - 1) == 0;
                } else {
                    f |= dfs(c, next);
                }
            }
        }
        dp[{a, turn}] = f;
    }
    return dp[{a, turn}];
}

void solve(ll k, vector<ll> a) {
    
    ll sub = INT_MAX;
    for(ll x : a) {
        sub = min(sub, x / k);
    }

    auto c = a;

    ll cnt = 0;
    for(ll &x : a) {
        x -= sub * k;
        cnt += x <= k;
    }
    assert(cnt);
    ll sum = accumulate(a.begin(), a.end(), 0LL);

    // cout << "upd a : " << a << endl;

    int res = sum >= k;
    
    cout << (res ? "Alice" : "Bob") << '\n';

    // if(!(res == dfs(c, k))) {
    //     cout << k << endl;
    //     cout << c << endl;
        
    //     assert(0);
    // }
    // assert(res == dfs(c, k));

}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    for(ll i = 0; i < casi; i++) {

        ll k; cin >> k;
        vector<ll> a(k + 1);
        for(ll &x : a) cin >> x;

        solve(k, a);
    }

    // for(int i = 0; i < 10000; i++) {
    //     int k = rng() % 5 + 1;
    //     vector<ll> a(k + 1);
    //     for(ll &x : a) x = rng() % k * 3 + 1;
    //     solve(k, a);
    // }

    // vector<ll> a = {1, 7, 10, 10, 10};
    // cout << dfs(a, 4) << endl;

    return 0;
}