#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    map<vector<string>, int> m;

    for(int i = 0; i + 8 <= n; i++) {
        set<string> s(a.begin() + i, a.begin() + i + 8);
        vector<string> b(a.begin() + i, a.begin() + i + 8);
        if(s.size() == 8) m[b]++;
    }

    int best = 0;
    vector<string> res;

    for(auto [melody, cnt] : m) {
        if(cnt > best) {
            best = cnt;
            res = melody;
        }
    }

    cout << best << '\n';
    if(best) {
        for(int i = 0; i < 8; i++) {
            cout << res[i] << " \n"[i == 7];
        }
    }

    return 0;
}
