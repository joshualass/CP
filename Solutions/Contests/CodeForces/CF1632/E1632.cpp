#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
algorithm
1. find furthest node from root and denote this node as L. 
 a. Observe that one endpoint of the edge we add we will be the root and the other endpoint will be somewhere along the path between the root and L
2. Let the weight of the edge be n and decrease 1 by 1
 a. Observe that the node for the endpoint of the edge goes along the path in an increasing manner starting at L
 b. Once a node can be reached quicker by taking the edge, we should ensure that it always can be and that the cost is <= cost of reaching L
3. Have a set of the elements that are not influenced by the edge, if the cost of root to one of the elements that is not influenced by the edge is 
>= the distance to node L after making the endpoint of the edge one point higher, then we can make the endpoint of the edge higher, 
still maintaining the sets
*/

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dr(n), dl(n), o;

    queue<array<int,3>> q;
    q.push({0, 0, -1});
    while(q.size()) {
        auto [i, d, p] = q.front();
        q.pop();
        dr[i] = d;
        o.push_back(i);
        for(int c : adj[i]) {
            if(c != p) {
                q.push({c, d + 1, i});
            }
        }
    }

    int l = o.back();
    q.push({l, 0, -1});
    while(q.size()) {
        auto [i, d, p] = q.front();
        q.pop();
        dl[i] = d;
        for(int c : adj[i]) {
            if(c != p) {
                q.push({c, d + 1, i});
            }
        }
    }

    vector<int> res(n+1);
    int d = 0;
    for(int x = n; x; x--) {
        //remove as much of the set as possible
        while(o.size() && x + dl[o.back()] - d <= dr[o.back()] && x + dl[o.back()] - d <= x + d) o.pop_back();
        while(dr[o.back()] > x + d) {
            d++; 
            while(o.size() && x + dl[o.back()] - d <= dr[o.back()] && x + dl[o.back()] - d <= x + d) o.pop_back();
        }
        res[x] = (o.size() == n ? dr[o.back()] : x + d);
    }

    for(int i = 1; i <= n; i++) {
        cout << res[i] << " \n"[i == n];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}