#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

vector<int> s1(int n, int k, string s) {

    vector<vector<int>> dp0(n,vector<int>(k+1));

    for(int i = 0; i <= k; i++) {
        int cnt = 0;
        int lo = -1;
        for(int hi = 0; hi < n; hi++) {
            cnt += s[hi] == '1';
            while(cnt > i) {
                lo++;
                cnt -= s[lo] == '1';
            }
            dp0[hi][i] = hi - lo;
            if(hi != 0) {
                dp0[hi][i] = max(dp0[hi][i], dp0[hi-1][i]);
            }
        }
    }

    // cout << "dp0\n" << dp0;

    vector<vector<int>> dp1(n,vector<int>(k+1));

    for(int i = 0; i <= k; i++) {
        int cnt = 0;
        int hi = n;
        for(int lo = n - 1; lo >= 0; lo--) {
            cnt += s[lo] == '0';
            while(cnt > i) {
                hi--;
                cnt -= s[hi] == '0';
            }
            dp1[lo][i] = hi - lo;
            if(lo != n - 1) {
                dp1[lo][i] = max(dp1[lo][i],dp1[lo+1][i]);
            }
        }
    }

    // cout << "dp1\n" << dp1;

    vector<int> bests(n+1,-1);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            // int val =  0;
            int val0 = (i == 0 ? 0 : dp0[i-1][j]);
            int val1 = (i == n ? 0 : dp1[i][k-j]);
            bests[val0] = max(bests[val0],val1);
        }
    }
    // cout << "bests : " << bests << '\n';
    vector<int> res(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            if(bests[j] != -1) {
                res[i] = max(res[i], (i + 1) * j + bests[j]);
            }
        }
    }

    return res;
}

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> v1 = s1(n,k,s);
    reverse(s.begin(), s.end());
    vector<int> v2 = s1(n,k,s);
    for(int i = 0; i < n; i++) {
        cout << max(v1[i], v2[i]) << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}