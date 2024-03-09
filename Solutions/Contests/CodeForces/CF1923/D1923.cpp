#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve1(vector<ll> &v, vector<int> &ans) {
    int n = v.size();
    vector<ll> pref(n + 1);
    vector<int> diff(n);
    for(int i = 0; i < n; i++) {
        pref[i+1] = pref[i];
        pref[i+1] += v[i];
        if(i != 0) {
            diff[i] = diff[i-1];
            if(v[i-1] != v[i]) diff[i]++;
        }
    }
    for(int i = 1; i < n; i++) {
        int l = 0, r = i - 1;
        if(v[i-1] > v[i]) l = i - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            ll sum = pref[i] - pref[m];
            int hasdiff = diff[i-1] - diff[m];
            if(sum > v[i] && (hasdiff || i - m == 1)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        ll sum = pref[i] - pref[l];
        int hasdiff = diff[i-1] - diff[l];
        if(sum > v[i] && (hasdiff || i - l == 1)) {
            ans[i] = min(ans[i], i - l);
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    vector<int> ans(n,INT_MAX);
    solve1(v,ans);
    reverse(v.begin(),v.end());
    reverse(ans.begin(),ans.end());
    solve1(v,ans);
    reverse(ans.begin(),ans.end());
    for(int i = 0; i < n; i++) {
        cout << (ans[i] == INT_MAX ? -1 : ans[i]) << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}