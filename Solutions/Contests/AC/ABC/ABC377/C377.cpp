#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;

    set<array<int,2>> s;

    vector<int> dx = {1,2,2,1,-1,-2,-2,-1}, dy = {2,1,-1,-2,-2,-1,1,2};

    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        s.insert({x,y});
        for(int j = 0; j < 8; j++) {
            int tx = x + dx[j], ty = y + dy[j];
            if(tx >= 1 && tx <= n && ty >= 1 && ty <= n) {
                s.insert({tx,ty});
            }
        }
    }

    cout << n * n - s.size() << '\n';

    return 0;
}