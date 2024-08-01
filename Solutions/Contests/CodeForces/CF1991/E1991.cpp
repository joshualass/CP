#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
Try see whether or not we can turn this graph into a 2 coloring graph. If it can be done, the Bob player can fill all 1's and 2's of the graph, if Alice queries 1 3 and 1's are filled, 
then we fill remaining 2's with 2's and 3's and this always works.
If there doesn't exist a 2-coloring. This implies that an odd cycle is present in the graph. We can play Alice and ask same 2 colors and it will be impossible for Bob to win here.
*/

void solve() {
    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<array<int,2>> q;
    set<int> red, blue;
    q.push({0,0});
    bool poss = 1;
    while(q.size()) {
        auto [i, p] = q.front();
        q.pop();

        if(red.count(i)) {
            if(p == 1) poss = 0;
            continue;
        }
        if(blue.count(i)) {
            if(p == 0) poss = 0;
            continue;
        }

        if(p == 0) {
            red.insert(i);
        } else {
            blue.insert(i);
        }

        for(int edge : adj[i]) {
            q.push({edge, p ^ 1});
        }

    }

    if(poss) {
        cout << "Bob" << endl;
        for(int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            if(a > b) swap(a,b);
            if(a == 1) {
                if(red.size()) {
                    cout << *red.begin() + 1 << " " << 1 << endl;
                    red.erase(red.begin());
                } else {
                    cout << *blue.begin() + 1 << " " << b << endl;
                    blue.erase(blue.begin());
                }
            } else {
                if(blue.size()) {
                    cout << *blue.begin() + 1 << " " << 2 << endl;
                    blue.erase(blue.begin());
                } else {
                    cout << *red.begin() + 1 << " " << b << endl;
                    red.erase(red.begin());
                }
            }
        }
    } else {
        cout << "Alice" << endl;
        for(int i = 0; i < n; i++) {
            cout << "1 2" << endl;
            int t1, t2; cin >> t1 >> t2;
        }
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}