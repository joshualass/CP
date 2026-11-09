#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> res;

    auto dfs = [&](auto self, string cur, int opens, int closes) -> void {
        if(sz(cur) && opens == closes) res.push_back(cur);
        if(opens) {
            string t = cur;
            t.push_back('(');
            self(self, t, opens - 1, closes);
        }
        if(opens < closes) {
            string t = cur;
            t.push_back(')');
            self(self, t, opens, closes - 1);
        }
    };

    dfs(dfs, "", 10, 10);

    vector<pair<array<int,2>, string>> rres;
    for(string s : res) {
        for(int k = 0; k * 2 <= sz(s); k++) {
            rres.push_back({{sz(s), k}, s});
        }
    }

    cout << sz(rres) << '\n';
    for(auto x : rres) {
        cout << x.first[0] << " " << x.first[1] << '\n';
        cout << x.second << '\n';
    }

    return 0;
}
