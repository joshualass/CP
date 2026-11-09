#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b; cin >> a >> b;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll res = 1;
    if(a != b) res = 0;
    map<char,int> m;
    for(char c : a) m[c]++;
    int p = 1;
    for(auto [k, v] : m) {
        for(int i = 1; i <= v; i++) {
            res *= p++;
            res /= i;
        }
    }

    cout << res << '\n';

    return 0;
}
