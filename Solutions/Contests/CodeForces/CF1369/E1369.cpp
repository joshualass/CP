#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> w(n);
    vector<array<int,2>> f(m);
    vector<set<int>> reqs(n);
    vector<bool> vis(n); 
    vector<int> order;

    for(int &x : w) cin >> x;

    queue<int> q;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        reqs[x].insert(i);
        reqs[y].insert(i);
        f[i] = {x,y};
    }

    //second handle handle reverse dfs
    for(int i = 0; i < n; i++) {
        if(w[i] >= reqs[i].size()) q.push(i);
    }

    while(q.size()) {
        int i = q.front();
        q.pop();
        if(vis[i]) continue;
        vis[i] = 1;
        for(int x : reqs[i]) {
            order.push_back(x);
            for(int y : f[x]) {
                if(y != i) {
                    reqs[y].erase(x);
                    if(reqs[y].size() <= w[y]) {
                        q.push(y);
                    }
                }
            }
        }
    }

    if(order.size() == m ) {
        cout << "ALIVE\n";
        reverse(order.begin(), order.end());
        for(int i = 0; i < m; i++) {
            cout << order[i] + 1 << " \n"[i == m - 1];
        }
    } else {
        cout << "DEAD\n";
    }

    return 0;
}