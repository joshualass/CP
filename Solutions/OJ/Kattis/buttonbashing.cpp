#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, t; cin >> n >> t;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    queue<array<int,2>> q;
    vector<int> vis(3601, -1);

    auto addq = [&](int time, int presses) -> void {
        time = max(0, min(3600, time));
        if(vis[time] == -1) {
            q.push({time, presses});
            vis[time] = presses;
        }
    };

    addq(0, 0);
    while(!q.empty()) {
        auto [time, presses] = q.front();
        q.pop();
        for(int x : a) {
            addq(time + x, presses + 1);
        }
    }

    for(int i = t; ; i++) {
        assert(i <= 3600);
        if(vis[i] != -1) {
            cout << vis[i] << " " << i - t << '\n';
            break;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}