#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    int ops = 0;
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        if(vis[x] == 0) {
            queue<int> q;
            q.push(x);
            while(q.size()) {
                int z = q.front();
                q.pop();
                if(vis[z]) continue;
                vis[z] = 1;
                ops++;
                q.push(a[z]);
            }
        }
        cout << ops << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}