    #include <bits/stdc++.h>
    typedef long long ll;
    typedef long double ld;
    using namespace std;
    const ll MOD = 1e9 + 7;
    
    // int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; /
    int dx[4]{1,0,-1,0}, dy[4]{0,1,0,-1}; //UP, RIGHT, DOWN, LEFT
    int n, sx, sy; 
    // int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};
    set<array<int,3>> vis;
    set<pair<int,int>> wtf;
    
    // bool escape = 0;
    
    // void dfs(array<int,3> a) {
    //     if(escape) return;
    //     pair<int,int> p = {a[0], a[1]};
    //     // cout << "x : " << p.first << " y : " << p.second << endl;
    //     if(vis.count(p)) return;
    //     vis.insert(p);
    //     int x = p.first, y = p.second;
    //     if(abs(x-sx) > 1e5 || abs(y-sy) > 1e5) {
    //         escape = 1;
    //     }
    //     for(int i = 3; i >= 0; i--) {
    //         int ai = (i + a[2]) % 4;
    //         // st.push({p.first + dx[ai], p.second + dy[ai], ai});
    //         dfs({p.first + dx[ai], p.second + dy[ai], ai});
    //     }   
    // }
    
    signed main() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        cin >> n >> sx >> sy;

        for(int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            wtf.insert({a,b});
            vis.insert({a,b,0});
            vis.insert({a,b,1});
            vis.insert({a,b,2});
            vis.insert({a,b,3});
        }
    
        int cnt = 0;
        int dir = 0;
        stack<array<int,3>> st;
        st.push({sx,sy});

        while(cnt++ < 8e6 && st.size()) {
            array<int,3> a = st.top();
            st.pop();
            // cout << "x : " << p.first << " y : " << p.second << endl;
            if(vis.count(a)) continue;
            vis.insert(a);
            
            // for(int i = 2; i >= -1; i--) {
            for(int i = 3; i >= 0; i--) {
                int ai = (i + a[2] + 4) % 4;
                st.push({a[0] + dx[ai], a[1] + dy[ai], ai});
            }
            int cx = a[0] + dx[(a[2] + 3) % 4] + dx[(a[2] + 2) % 4];
            int cy = a[1] + dy[(a[2] + 3) % 4] + dy[(a[2] + 2) % 4];
            if(wtf.count({cx,cy}) && vis.count({cx,cy,(a[2] + 3) % 4}) == 0) {
                st.push({cx,cy,(a[2] + 3) % 4});
            }
            //     int ai = (i + a[2]) % 4;
            //     st.push({a[0] + dx[ai], a[1] + dy[ai], ai});
            // }   
            if(abs(a[0]-sx) > 1e5 || abs(a[1]-sy) > 1e5) {
                cout << "NOT CONTAINED\n";
                return 0;
            }
        }
        cout << "CONTAINED\n";
        return 0;
    }