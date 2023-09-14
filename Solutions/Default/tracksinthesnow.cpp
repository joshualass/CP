#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<pair<int,int>> dirs = {{0,-1},{0,1},{-1,0},{1,0}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C; cin >> R >> C;

    vector<string> v(R);
    for(auto &x: v) cin >> x;
    vector<vector<bool>> visited(R,vector<bool>(C,false));
    int cnts = 0;
    queue<pair<int,int>> rabbits;
    queue<pair<int,int>> foxes;
    if(v[0][0] == 'R') {
        rabbits.push({0,0});
    } else if(v[0][0] == 'F') {
        foxes.push({0,0});
    }
    while(true) {
        // cout << "rabbits: " << rabbits.size() << " foxes: " << foxes.size() << "\n";
        if(rabbits.size()) {
            while(rabbits.size()) {
                pair<int,int> p = rabbits.front();
                rabbits.pop();
                if(visited[p.first][p.second]) {
                    continue;
                }
                // cout << "rabbit bfs: " << p.first << " " << p.second << "\n";
                visited[p.first][p.second] = true;
                for(auto x : dirs) {
                    int r = p.first + x.first;
                    int c = p.second + x.second;
                    if(r >= 0 && r < R && c >= 0 && c < C) {
                        if(v[r][c] == 'F' && !visited[r][c]) {
                            foxes.push({r,c});
                        } else if(v[r][c] == 'R' && !visited[r][c]) {
                            rabbits.push({r,c});
                        }
                    }
                }
            }
        } else if(foxes.size()) {  
            while(foxes.size()) {
                pair<int,int> p = foxes.front();
                foxes.pop();
                if(visited[p.first][p.second]) {
                    continue;
                }
                // cout << "fox bfs: " << p.first << " " << p.second << "\n";
                visited[p.first][p.second] = true;
                for(auto x : dirs) {
                    int r = p.first + x.first;
                    int c = p.second + x.second;
                    if(r >= 0 && r < R && c >= 0 && c < C) {
                        if(v[r][c] == 'F' && !visited[r][c]) {
                            foxes.push({r,c});
                        } else if(v[r][c] == 'R' && !visited[r][c]) {
                            rabbits.push({r,c});
                        }
                    }
                }
            }
        } else {
            break;
        }
        cnts++;
    }
    cout << cnts << "\n";
    return 0;
}