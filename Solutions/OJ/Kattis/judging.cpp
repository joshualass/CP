#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string,int> m1, m2;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        m1[s]++;
    }
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        m2[s]++;
    }
    int res = 0;
    for(auto [u, v] : m1) {
        res += min(v, m2[u]);
    }
    cout << res << '\n';
    return 0;
}