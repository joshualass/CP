#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> a(n,-1);
    vector<int> p(n+1);
    for(int i = 1; i <= n; i++) {
        p[i] = p[i-1] + (s[i-1] == '1');
    }

    // cout << "p : " << p << '\n';

    for(int i = n - 1; i >= 0; i--) {
        if(n - i <= k) {
            if(p[n] - p[i] == n - i) {
                a[i] = 1;
            }
            if(p[n] - p[i] == 0) {
                a[i] = 0;
            }
        } else {
            if(p[i+k] - p[i] == k && a[i+k] == 0) {
                a[i] = 1;
            }
            if(p[i+k] - p[i] == 0 && a[i+k] == 1) {
                a[i] = 0;
            }
        }
    }

    // cout << "a : " << a << '\n';

    vector<int> b(n,-1);
    for(int i = 0; i < n; i++) {
        if(i < k) {
            if(p[i+1] == i + 1) {
                b[i] = 1;
            } 
            if(p[i+1] == 0) {
                b[i] = 0;
            }
        } else {
            if(b[i-1] != -1) {
                if(i % k == 0) {
                    if(p[i+1] - p[i] != b[i-1] ) {
                        b[i] = p[i+1] - p[i];
                    }
                } else {
                    if(p[i+1] - p[i] == b[i-1]) {
                        b[i] = p[i+1] - p[i];
                    }
                }
            }
        }
    }

    // cout << "b : " << b << '\n';
    int res = -1;
    for(int i = 0; i < n - 1; i++) {
        if(b[i] != -1 && a[i+1] != -1) {
            if((n / k) & 1) {
                if(s[i+1] == s[0]) {
                    res = i + 1;
                }
            } else {
                if(s[i+1] != s[0]) {
                    res = i + 1;
                }
            }
        }
    }
    if(b[n-1] != -1) res = n;
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}