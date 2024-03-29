#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << "\n";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(string &x : a) cin >> x;
    for(int i = 0; i < 1000; i++) {
        for(int j = 0; j < n - 2; j++) {
            for(int k = 0; k < m - 2; k++) {
                set<char> seen;
                for(int l = 0; l < 3; l++) {
                    for(int o = 0; o < 3; o++) {
                        seen.insert(a[j+l][k+o]);
                    }
                }
                if(seen.size() == 1 && seen.count('W') == 0 || seen.size() == 2 && seen.count('\0') && seen.count('W') == 0) {
                    for(int l = 0; l < 3; l++) {
                        for(int o = 0; o < 3; o++) {
                            a[j+l][k+o] = '\0';
                        }
                    }
                }
            }
        }
    }
    // cout << "a\n" << a;
    bool ok = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] != '\0' && a[i][j] != 'W') {
                ok = 0;
            }
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}