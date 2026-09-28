#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;

    auto work = [&](string s, char c) -> int {
        int r = 1;
        for(int i = 0; i < n; i++) r *= 3;

        auto dfs = [&](auto self, int l, int r) -> int {
            int len = r - l;
            if(len == 1) {
                if(s[l] == c) {
                    return 0;
                } else {
                    return 1;
                }
            }
            int c0 = self(self, l, l + len / 3);
            int c1 = self(self, l + len / 3, l + len / 3 * 2);
            int c2 = self(self, l + len / 3 * 2, r);
            // cout << "l : " << l << " r : " << r << " c : " << c << " c0 : " << c0 << " c1 : " << c1 << " c2 : " << c2 << '\n';
            return min({c0+c1+c2, c0+c1, c0+c2,c1+c2});
        };
        return dfs(dfs,0,r);
    };

    cout << max(work(s,'0'), work(s,'1')) << '\n';

    return 0;
}