#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// SOLUTION_BEGIN
#include <bits/stdc++.h>
class ConnectingPoints {
public:
    int shortestWires(int N, vector<int> X, vector<int> Y) {
        vector<int> dx = {0,1,0,-1};
        vector<int> dy = {1,0,-1,0};
        vector board(N,vector<int>(N));
        auto reset = [&]() -> void {
            board = vector<vector<int>>(N, vector<int>(N));
            for(int i = 0; i < 4; i++) {
                board[X[i]][Y[i]] = 1;
            }
        };
        auto find_path = [&](int s, int t) -> int {
            int sx = X[s], sy = Y[s], tx = X[t], ty = Y[t];
            board[sx][sy] = 0;
            board[tx][ty] = 0;
            vector<vector<array<int,2>>> p(N,vector<array<int,2>>(N,{-1,-1}));
            queue<array<int,4>> q;
            q.push({sx,sy});
            while(q.size()) {
                auto [x, y, px, py] = q.front();
                q.pop();
                if(p[x][y] != array<int,2>{-1,-1} || board[x][y]) continue;
                p[x][y] = {px,py};
                if(x == tx && y == ty) {
                    int cnt = 0;
                    
                    while(array<int,2>{x,y} != array<int,2>{sx,sy}) {
                        cnt++;
                        board[x][y] = 1;
                        int nx = p[x][y][0];
                        int ny = p[x][y][1];
                        x = nx, y = ny;
                    }
                    board[x][y] = 1;
                    return cnt;
                }
                for(int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx >= 0 && nx < N && ny >= 0 && ny < N) {
                        q.push({nx,ny,x,y});
                    }
                }
            }
            return -1;
        };
        reset();
        int a_first = find_path(0,1);
        int a_second = find_path(2,3);
        reset();
        int b_first = find_path(2,3);
        int b_second = find_path(0,1);
        if(a_second == -1 && b_second == -1) {
            return -1;
        }
        int res = INT_MAX;
        if(a_second != -1) res = min(res, a_first + a_second);
        if(b_second != -1) res = min(res, b_first + b_second);
        return res;
    }
};
// SOLUTION_END

int main() {
  int arg0;
  cin >> arg0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n1; cin >> n1;
  vector<int> arg1(n1);
  for (int i=0;i<n1;++i) { cin >> arg1[i]; }
  int n2; cin >> n2;
  vector<int> arg2(n2);
  for (int i=0;i<n2;++i) { cin >> arg2[i]; }
  auto c = ConnectingPoints();
  int ret = c.shortestWires(arg0, arg1, arg2);
  cout << ret;
}