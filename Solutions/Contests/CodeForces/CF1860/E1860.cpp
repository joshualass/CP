#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
Used editorial for this problem

My thoughts before reading editorial
Try to compute something like
the distance between all pairs of pairs of letters
the distance between every position to any position between a specific pair
Not sure how to compute these as well as how to use these to help solve the queries

Idea used
Need to create an extra node representing every pair of letters. When we visit this node, we visit all the nodes.
We use this and a 0-1 BFS to precompute the distances between every pair of letters to every node. 

For our queries, we can either choose to travel without using operation of type 3 and our answer is just the distance between the 2 nodes
If we choose to use the operation of type 3, we use our precomputed values, and take the minimum distance trying to visit all the dummy nodes. 

*/

int dir[2] = {1,-1};

int d[676][50000];
vector<int> pos[676];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 676; i++) {
        for(int j = 0; j < 50000; j++) {
            d[i][j] = -1;
        }
    }
    
    string s; cin >> s;
    int n = s.size();

    for(int i = 1; i < n; i++) {
        int v = (s[i - 1] - 'a') + 26 * (s[i] - 'a');
        pos[v].push_back(i);
    }
    
    for(int i = 0; i < 676; i++) {
        queue<array<int,2>> q;
        q.push({i + n, 0});
        vector<bool> vis(676);
        while(q.size()) {
            array<int,2> a = q.front();
            q.pop();
            if(a[0] >= n) {
                a[0] -= n;
                if(vis[a[0]]) continue;
                vis[a[0]] = 1;
                for(int c : pos[a[0]]) {
                    if(d[i][c] != -1) continue;
                    d[i][c] = a[1];
                    for(int j = 0; j < 2; j++) {
                        if(c + dir[j] >= 1 && c + dir[j] < n && d[i][c + dir[j]] == -1) {
                            q.push({c + dir[j], a[1] + 1});
                        }
                    }
                }
            } else {
                if(d[i][a[0]] != -1) continue;
                d[i][a[0]] = a[1];
                for(int j = 0; j < 2; j++) {
                    if(a[0] + dir[j] >= 1 && a[0] + dir[j] < n && d[i][a[0] + dir[j]] == -1) {
                        q.push({a[0] + dir[j], a[1] + 1});
                    }
                }
                int v = (s[a[0] - 1] - 'a') + 26 * (s[a[0]] - 'a');
                if(!vis[v]) {
                    q.push({n + v, a[1] + 1});
                }
            }
        }
    }

    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int f, t; cin >> f >> t;
        int res = abs(f-t);
        for(int u = 0; u < 676; u++) {
            if(pos[u].size()) {
                res = min(res, d[u][f] + d[u][t] + 1);
            }
        }
        cout << res << '\n';
    }

    return 0;
}