#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<int> w(n);
    vector<array<int,2>> f(m);
    vector<set<int>> reqs(n);
    vector<bool> vis(n); 
    vector<int> order1;
    vector<int> order2;

    for(int &x : w) cin >> x;

    queue<int> q;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        reqs[x].insert(i);
        reqs[y].insert(i);
        f[i] = {x,y};
        if(w[x] == 0) q.push(x);
        if(w[y] == 0) q.push(y);
    }


    //first handle required 0 fooders
    while(q.size()) {
        int i = q.front();
        q.pop();
        // cout << "q1 i : " << i << '\n';
        if(vis[i]) continue;
        vis[i] = 1;
        for(int x : reqs[i]) {
            for(int y : f[x]) {
                if(y != i) {
                    // cout << "x : " << x << " y : " << y << '\n';
                    // cout << "w : " << w << '\n';
                    if(w[y]) {
                        order1.push_back(x);
                        w[y]--;
                        reqs[y].erase(x);
                        if(w[y] == 0) q.push(y);
                    } else {
                        cout << "DEAD\n";
                        return 0;
                    }
                }
            }
        }
    }

    // cerr << "ok phase2\n";

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
            order2.push_back(x);
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

    if(order1.size() + order2.size() == m ) {
        cout << "ALIVE\n";
        int m1 = order1.size();
        for(int i = 0; i < m1; i++) {
            cout << order1[i] + 1 << " \n"[i == m1 - 1];
        }

        int m2 = order2.size();
        reverse(order2.begin(), order2.end());
        for(int i = 0; i < m2; i++) {
            cout << order2[i] + 1 << " \n"[i == m2 - 1];
        }
    } else {
        cout << "DEAD\n";
    }

    return 0;
}