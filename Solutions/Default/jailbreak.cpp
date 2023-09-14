#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void printMat(vector<vector<int>>& mat) {
    cout << '\n';
    for(vector<int> x : mat) {
        for(int y : x) {
            cout << (y % 10) << " ";
        }
        cout << '\n';
    }
}

void BFS(vector<vector<int>>& v, int R, int C, vector<vector<char>>& board, vector<pair<int,int>> edges) {
    priority_queue<vector<int>> q;
    for(int i = 0; i < edges.size(); i++) {
        q.push({0,edges[i].first,edges[i].second});
    }
    // q.push({startR,startC, 0});
    while(q.size()) {
        vector<int> arr = q.top();
        q.pop();
        int r = arr[1];
        int c = arr[2];
        int doors = arr[0];
        if(r == -1 || r == R || c == -1 || c == C) {
            continue;
        }
        if(board[r][c] == '*') {
            continue;
        }
        if(board[r][c] == '#') {
            doors++;
        }
        if(INT_MAX == v[r][c]) {
            v[r][c] = doors;
            q.push({doors,r-1,c});
            q.push({doors,r+1,c});
            q.push({doors,r,c-1});
            q.push({doors,r,c+1});
        }
    }
}

void BFS2(vector<vector<int>>& v, int startR, int startC, int R, int C, vector<vector<char>>& board) {
    queue<vector<int>> q;
    q.push({startR,startC, 0});
    while(q.size()) {
        vector<int> arr = q.front();
        q.pop();
        int r = arr[0];
        int c = arr[1];
        int doors = arr[2];
        if(r == -1 || r == R || c == -1 || c == C) {
            continue;
        }
        if(board[r][c] == '*') {
            continue;
        }
        if(doors < v[r][c]) {
            v[r][c] = doors;
        if(board[r][c] == '#') {
            doors++;
        }
            q.push({r-1,c,doors});
            q.push({r+1,c,doors});
            q.push({r,c-1,doors});
            q.push({r,c+1,doors});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int R, C; cin >> R >> C;
        vector<vector<char>> v(R,vector<char>(C));
        vector<pair<int,int>> starts(0);
        vector<pair<int,int>> edges(0);
        for(int r = 0; r < R; r++) {
            string next; cin >> next;
            for(int c = 0; c < C; c++) {
                v[r][c] = next[c]; 
                if(next[c] == '$') {
                    starts.push_back({r,c});
                }
                if((next[c] == '#' || next[c] == '.') && (r == 0 || r == R-1 || c == 0 || c == C-1)) {
                    edges.push_back({r,c});
                }
            }
        }
        vector<vector<int>> A(R,vector<int>(C,INT_MAX));
        vector<vector<int>> B(R,vector<int>(C,INT_MAX));
        vector<vector<int>> CC(R,vector<int>(C,INT_MAX));

        BFS2(A, starts[0].first, starts[0].second, R, C, v);
        BFS2(B, starts[1].first, starts[1].second, R, C, v);
        // BFS(A, R, C, v, {{starts[0].first,starts[0].second}});
        // BFS(B, R, C, v, {{starts[1].first,starts[1].second}});

        BFS(CC, R, C, v, edges);
        
        int least = INT_MAX;
        for(int r = 0; r < R; r++) { 
            for(int c = 0; c < C; c++) {
                if(v[r][c] != '*') {
                    least = min(least, A[r][c] + B[r][c] + CC[r][c]);
                }
            }
        }

        // printMat(A);
        // printMat(B);
        // printMat(CC);
        cout << least << '\n';
    }

    return 0;
}