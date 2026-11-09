#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    int q; cin >> q;
    map<string,vector<int>> m;
    for(int qq = 0; qq < q; qq++) {
        string s; cin >> s;
        m[s].push_back(qq);
    }

    map<string,int> adds;
    vector<int> res(q);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= sz(a[i]); j++) {
            adds[a[i].substr(0, j)]++;
        }
        if(m.count(a[i])) {
            int ans = 0;
            for(int j = 0; j <= sz(a[i]); j++) {
                ans += adds[a[i].substr(0, j)];
            }
            for(int x : m[a[i]]) res[x] = ans;
            m.erase(a[i]);
        }
    }

    for(auto [s, v] : m) {
        int ans = 0;
        for(int j = 0; j <= sz(s); j++) {
            ans += adds[s.substr(0, j)];
        }
        for(int y : v) res[y] = ans;
    }

    for(int x : res) cout << x << '\n';

    return 0;
}
