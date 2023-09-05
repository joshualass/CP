#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C;
    cin >> R >> C;
    vector<vector<char>> mat(R, vector<char>(C));
    vector<vector<int>> map(R, vector<int>(C));
    for(int i = 0; i < R; i++) {
        string line;
        cin >> line;
        for(int t = 0; t < C; t++) {
            mat[i][t] = line[t];
        }
    }

    int comp = 0;

    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            if(map[r][c] == 0) {
                comp++;
                char type = mat[r][c];
                queue<pair<int,int>> q {};
                q.push(make_pair(r,c));
                while(!q.empty()) {
                    pair<int,int> p = q.front();
                    q.pop();
                    int row = p.first;
                    int col = p.second;
                    if(row >= 0 && row < R && col >= 0 && col < C && mat[row][col] == type && map[row][col] == 0) {
                        map[row][col] = comp;
                        q.push(make_pair(row-1,col));
                        q.push(make_pair(row+1,col));     
                        q.push(make_pair(row,col+1));
                        q.push(make_pair(row,col-1));                    
                    }
                }
            }
        }
    }

    int n;
    cin >> n;

    // for(vector<int> x : map) {
    //     for(int y : x) {
    //         cout << y << " ";
    //     }
    //     cout << "\n";
    // }

    for(int i = 0; i < n; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--;
        c1--;
        r2--;
        c2--;
//        cout << r1 << " " << c1 << " " << r2 << " " << c2;
        if(map[r1][c1] == map[r2][c2]) {
            if(mat[r1][c1] == '1') {
                cout << "decimal" << "\n";
            } else {
                cout << "binary" << "\n";
            }
        } else {
            cout << "neither" << "\n";
        }
    }


    return 0;
}