#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<array<ll,2>>> a(2);
    for(int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        a[(x+y)&1].push_back({x,y});
    }
    ll res = 0;
    for(auto b : a) {
        if(!b.empty()) {
            sort(b.begin(), b.end(), [](const auto &lhs, const auto &rhs) {
                return lhs[1] - lhs[0] < rhs[1] - rhs[0];
            });
            ll curr = 0, prev = b[0][1] - b[0][0];
            for(int i = 0; i < b.size(); i++) {
                ll next = b[i][1] - b[i][0];
                curr += (next - prev) * i;
                res += curr;
                prev = next;
            }
            sort(b.begin(), b.end(), [](const auto &lhs, const auto &rhs) {
                return lhs[0] + lhs[1] < rhs[0] + rhs[1];
            });

            curr = 0, prev = b[0][0] + b[0][1];
            for(int i = 0; i < b.size(); i++) {
                ll next = b[i][0] + b[i][1];
                curr += (next - prev) * i;
                res += curr;
                prev = next;
            }
        }

    }

    cout << (res >> 1) << '\n';


    return 0;
}