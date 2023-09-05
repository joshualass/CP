#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printAdj(const vector<vector<int>> &adj) {
    cout << " --- adjlist --- \n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i - " << i << ':';
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}

void printV(const vector<int> &x) {
    cout << " --- vector --- \n";
    for(int y : x) {
        cout << y << " ";
    }
    cout << "\n";
}

vector<pair<int,int>> directions = {{0,-1},{0,1},{1,0},{-1,0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    int startR, startC;
    int endR, endC;
    vector<vector<int>> map(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        // cout << "word: " << word << "\n";
        for (int t = 0; t < m; t++) {
            switch (word[t]) {
                case '#':
                    map[i][t] = -1;
                    break;
                case '.':
                    map[i][t] = 1;
                    break;
                case 'F':
                    if (k >= 2) {
                        map[i][t] = 2;
                    } else {
                        map[i][t] = -1;
                    }
                    break;
                case 'M':
                    if(k >= 3) {
                        map[i][t] = 3;
                    } else {
                        map[i][t] = -1;
                    }
                    break;
                default:
                    map[i][t] = 0;
            }
            if (word[t] == 'S') {
                startR = i;
                startC = t;
            }
            if (word[t] == 'G') {
                endR = i;
                endC = t;
            }
        }
    }
    // printAdj(map);
    
    // cout << "startR: " << startR << " startC: " << startC << "\n";
    vector<vector<bool>> visited(n, vector<bool>(m));

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({1,k,startR,startC});
    int mindays = -1;
    while(pq.size()) {
        vector<int> v = pq.top();
        // printV(v);
        pq.pop();
        if(v[2] == endR && v[3] == endC) {
            mindays = v[0];
            break;
        }
        visited[v[2]][v[3]] = true;
        for(int i = 0; i < 4; i++) {
            pair<int,int> p = directions[i];
            int newR = v[2] + p.first;
            int newC = v[3] + p.second;
            if(newR >= 0 && newR < n && newC >= 0 && newC < m && map[newR][newC] != -1 && !visited[newR][newC]) {
                if(v[1] - map[newR][newC] < 0) {
                    pq.push({v[0]+1,k-map[newR][newC],newR,newC});
                } else {
                    pq.push({v[0],v[1]-map[newR][newC],newR,newC});
                }
            } 
        }
    } 
    cout << mindays << "\n";
    return 0;
}