// https://open.kattis.com/problems/crystalcrosswind
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int X, Y, K; cin >> X >> Y >> K;
    vector<vector<vector<pair<int,int>>>> deps(X, vector<vector<pair<int, int>>>(Y));
    vector<vector<vector<pair<int,int>>>> rev_deps(X, vector<vector<pair<int, int>>>(Y));
    vector<vector<int>> vals(X,vector<int>(Y,-1)); // -1 - no information/dependencies, 0 - never possible, 1 - necessary
    
    for(int i = 0; i < K; i++) {
        int dx, dy, b; cin >> dx >> dy >> b;
        queue<pair<int,int>> q;
        vector<vector<bool>> visited(X, vector<bool>(Y));
        for(int j = 0; j < b; j++) {
            int x, y; cin >> x >> y;
            x--; y--;
            vals[x][y] = 1;
            visited[x][y] = 1;
            q.push({x+dx,y+dy});
            if(x - dx >= 0 && x - dx < X && y - dy >= 0 && y - dy < Y) {
                vals[x-dx][y-dy] = 0;
                visited[x-dx][y-dy] = 1;
            }
        }
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            int x = p.first, y = p.second;
            if(x < 0 || x >= X || y < 0 || y >= Y) continue;
            if(visited[x][y]) continue;
            visited[x][y] = 1;
            deps[x][y].push_back({x-dx,y-dy});
            rev_deps[x-dx][y-dy].push_back({x,y});
            q.push({x + dx, y + dy});
        }
        // cout << "i : " << i << " visited \n" << visited << '\n';
        for(int x = 0; x < X; x++) {
            for(int y = 0; y < Y; y++) {
                if(!visited[x][y]) {
                    vals[x][y] = 0;
                }
            }
        }
        // cout << "vals \n" << vals;
    }

    // cout << "vals \n" << vals;
    vector<vector<bool>> visited(X, vector<bool>(Y));

    queue<pair<int,int>> q;
    for(int x = 0; x < X; x++) {
        for(int y = 0; y < Y; y++) {
            if(vals[x][y] == 1) {
                q.push({x,y});
            }
        }
    }

    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        int x = p.first, y = p.second;
        if(x < 0 || x >= X || y < 0 || y >= Y) {
            continue;
        }
        if(visited[x][y] || vals[x][y] == 0) continue;
        visited[x][y] = 1;
        vals[x][y] = 1;
        for(auto dep : deps[x][y]) {
            q.push(dep);
        }
    }
    visited = vector<vector<bool>>(X, vector<bool>(Y));
    for(int x = 0; x < X; x++) {
        for(int y = 0; y < Y; y++) {
            if(vals[x][y] == 0) {
                q.push({x,y});
            }
        }
    }

    while(q.size()) {
        pair<int,int> p = q.front();
        q.pop();
        int x = p.first, y = p.second;
        if(x < 0 || x >= X || y < 0 || y >= Y) {
            continue;
        }
        if(visited[x][y] || vals[x][y] == 1) continue;
        visited[x][y] = 1;
        vals[x][y] = 0;
        for(auto dep : rev_deps[x][y]) {
            q.push(dep);
        }
    }

    // cout << "vals \n" << vals;

    for(int y = 0; y < Y; y++) {
        for(int x = 0; x < X; x++) {
            if(vals[x][y] == 1) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    cout << '\n';

    for(int y = 0; y < Y; y++) {
        for(int x = 0; x < X; x++) {
            if(vals[x][y] != 0) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}