#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT
int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1};
int n, sx, sy; 
int cnt = 0;
// int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};
set<pair<int,int>> vis;

bool escape = 0;

void dfs(array<int,3> a) {
    if(escape || cnt++ > 1e6) return;
    pair<int,int> p = {a[0], a[1]};
    // cout << cnt << '\n';
    cout << "x : " << p.first << " y : " << p.second << endl;
    if(vis.count(p)) return;
    vis.insert(p);
    int x = p.first, y = p.second;
    if(abs(x-sx) > 1e5 || abs(y-sy) > 1e5) {
        escape = 1;
    }
    for(int i = 0; i < 4; i++) {
        int ai = (i + a[2]) % 4;
        // st.push({p.first + dx[ai], p.second + dy[ai], ai});
        dfs({p.first + dx[ai], p.second + dy[ai], ai});
    }   
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> sx >> sy;
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        vis.insert({a,b});
    }

    // int cnt = 0;
    // int dir = 0;
    // stack<array<int,3>> st;
    // st.push({sx,sy});
    // while(cnt++ < 5e6 && st.size()) {
    //     array<int,3> a = st.top();
    //     st.pop();
    //     pair<int,int> p = {a[0], a[1]};
    //     // cout << "x : " << p.first << " y : " << p.second << endl;
    //     if(vis.count(p)) continue;
    //     vis.insert(p);
    //     for(int i = 3; i >= 0; i--) {
    //         int ai = (i + a[2]) % 4;
    //         st.push({p.first + dx[ai], p.second + dy[ai], ai});
    //     }   
    //     int x = p.first, y = p.second;
    //     if(abs(x-sx) > 1e5 || abs(y-sy) > 1e5) {
    //         cout << "NOT CONTAINED\n";
    //         return 0;
    //     }
    // }
    dfs({sx,sy,0});
    cout << (escape ? "NOT CONTAINED" : "CONTAINED") << '\n';
    return 0;
}