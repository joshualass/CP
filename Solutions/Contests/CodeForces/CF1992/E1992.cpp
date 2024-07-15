#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s = to_string(n);

    vector<array<int,2>> ans;

    for(int a = 1; a <= 10000; a++) {
        for(int ss = 1; ss <= 8; ss++) {

            int b = s.size() * a - ss;
            if(b > 10000 || b == 0) continue;

            string res1 = "";
            for(int i = 0; i < ss; i++) {
                res1.push_back(s[i % s.size()]);
            }
            int res2 = n * a - b;
            if(stoi(res1) == res2) {
                ans.push_back({a,b});
            }
        }
    }

    cout << ans.size() << '\n';
    for(auto a : ans) {
        cout << a[0] << " " << a[1] << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}