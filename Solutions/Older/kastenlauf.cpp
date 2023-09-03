#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(vector<bool>& x) {
    for (int y : x) {
        cout << y << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    while(tc-->0) {
        int n; cin >> n;
        vector<pair<int,int>> coords(n+2); // 0 -> 1
        for(int i = 0; i < n + 2; i++) {
            int x, y; cin >> x >> y;
            coords[i] = {x,y};
        }
        vector<vector<int>> adj(n+2);
        vector<bool> visited(n+2,false);
        for(int i = 0; i < n + 2; i++) {
            for(int j = i + 1; j < n + 2; j++) {
                int distance = abs(coords[i].first - coords[j].first) + abs(coords[i].second - coords[j].second);
                if(distance <= 1000) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        queue<int> q;
        q.push(0);
        while(q.size()) {
            int f = q.front();
            q.pop();
            if(visited[f]) {
                continue;
            }
            visited[f] = true;
            for(int x : adj[f]) {
                q.push(x);
            }
        }
        // cout << "visited:\n";
        // printV(visited);
        cout << (visited[n+1] ? "happy" : "sad") << "\n";
    }

    return 0;
}