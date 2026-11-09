#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<array<int,2>> vis;
    queue<array<int,3>> q;
    int x, y; cin >> x >> y;

    auto addq = [&](int s, int r, int t) -> void {
        if(vis.count({s, r}) == 0) {
            vis.insert({s, r});
            q.push({s, r, t});
        }
    };
    
    addq(x % 10, y % 10, 0);

    while(!q.empty()) {
        auto [s, r, t] = q.front();
        q.pop();

        if(s == 6 && r == 7) {
            cout << t << '\n';
            return 0;
        }

        addq((s + 1) % 10, r, t + 1);
        addq((r + 1) % 10, s, t + 1);
    }

    return 0;
}
