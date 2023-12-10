#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> adj(n * n);
    vector<vector<int>> deps(n * n);

    vector<string> board(n);

    for(auto &x: board) cin >> x;

    for(int row = 0; row < n; row++) {
        vector<int> points;
        for(int col = 0; col < n; col++) {
            if(board[row][col] == 'P') {
                // cout << "pb: " << row * n + col << '\n';
                points.push_back(row * n + col);
            }
        }
        if(points.empty()) continue;
        points.push_back(points.front());
        for(int i = 0; i + 1 < points.size(); i++) {
            adj[points[i]].push_back(points[i+1]);
            deps[points[i+1]].push_back(points[i]);
        }
    }

    for(int col = 0; col < n; col++) {
        vector<int> points;
        for(int row = 0; row < n; row++) {
            if(board[row][col] == 'P') {
                points.push_back(row * n + col);
            }
        }
        if(points.empty()) continue;
        points.push_back(points.front());
        for(int i = 0; i < points.size() - 1; i++) {
            adj[points[i]].push_back(points[i+1]);
            deps[points[i+1]].push_back(points[i]);
        }        
    }

    ll ans = 1;

    vector<bool> to(n * n);   //this tile has a directed path
    vector<bool> from(n * n); //there is a path that goes to this tile


    for(int i = 0; i < n * n; i++) {
        if(!to[i] && board[i / n][i % n] == 'P') {
            ans <<= 1;
            queue<int> q;
            to[i] = true;
            from[adj[i][0]] = true;
            cout << "point machine: " << i << '\n';
            q.push(i);
            q.push(adj[i][0]);
            while(q.size()) {
                int num = q.front();
                q.pop();
                if(to[num] && from[num]) {
                    continue;
                }
                //check if this can only go to one location
                if(!to[num]) { //no directed path from this node
                    int l = adj[num][0];
                    int r = adj[num][1];
                    
                    if(from[l]) { //make path to r
                        to[num] = true;
                        from[r] = true;
                        q.push(r);
                    }
                    if(from[r]) { //make path to l
                        to[num] = true;
                        from[l] = true;
                        q.push(l);
                    }

                }
                if(!from[num]) { //no directed path goes to this node
                    int parent1 = deps[num][0];
                    int parent2 = deps[num][1];

                    if(from[adj[parent1][0]] || from[adj[parent1][1]]) { // this parent has one of its children alread frommed
                        from[num] = true;
                        to[parent1] = true;
                        q.push(parent1);
                    }
                    if(from[adj[parent2][0]] || from[adj[parent2][1]]) { // this parent has one of its children alread frommed
                        from[num] = true;
                        to[parent2] = true;
                        q.push(parent2);
                    }                    
                }

            }
        }
    }

    cout << ans << '\n';

    return 0;
}