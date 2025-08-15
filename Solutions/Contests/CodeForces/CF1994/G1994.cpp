#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    int ln = 32 - __builtin_clz(n - 1);

    string s; cin >> s;
    reverse(s.begin(), s.end());
    vector<int> a(k);
    for(int i = 0; i < k; i++) a[i] = s[i] == '1';

    vector<int> c0(k), c1(k);
    for(int i = 0; i < n; i++) {
        string num; cin >> num;
        reverse(num.begin(), num.end());
        for(int j = 0; j < k; j++) {
            if(num[j] == '0') {
                c0[j]++;
            } else {
                c1[j]++;
            }
        }
    }

    // cout << "c0 : " << c0 << "\n";
    // cout << "c1 : " << c1 << "\n";

    vector dp(k + 1, vector<array<int,2>>(1 << ln, {-1, -1}));
    dp[0][0] = {-2,-2};
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < 1 << ln; j++) {
            if(dp[i][j][0] != -1) {
                int t0 = j + c1[i], t1 = j + c0[i];
                if((t0 & 1) == a[i]) {
                    dp[i+1][t0 >> 1] = {0, j};
                }
                if((t1 & 1) == a[i]) {
                    dp[i+1][t1 >> 1] = {1, j};
                }
            }
        }
    }

    if(dp[k][0][0] == -1) {
        cout << "-1\n";
        return;
    }

    string res = "";
    for(int i = k, cur = 0; i; i--) {
        res.push_back('0' + dp[i][cur][0]);
        cur = dp[i][cur][1];
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}