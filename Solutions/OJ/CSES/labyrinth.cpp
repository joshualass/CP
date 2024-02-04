#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //DOWN, UP, RIGHT, LEFT

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

void printV(const vector<char> &x) {
    for(auto y : x) {
        cout << y;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C; cin >> R >> C;
    int sR, sC = -1;
    vector<string> v(R);
    for(int i = 0;i  < R; i++) {
        cin >> v[i];
        for(int j = 0; j < C; j++) {
            if(v[i][j] == 'A') {
                sR = i;
                sC = j;
            }
        }
    }

    vector<vector<int>> parents(R, vector<int>(C,-1));
    queue<vector<int>> q;
    vector<char> ans(0);
    q.push({sR, sC, 1});
    while(q.size()) {
        vector<int> p = q.front();
        q.pop();
        int r = p[0];
        int c = p[1];
        int dir = p[2];
        if(parents[r][c] == -1 && v[r][c] != '#') {
            if(v[r][c] == 'B') {
                // cout << "r: " << r << " c: " << c << " dir: " << dir << "\n";
                while(v[r][c] != 'A') {
                    switch(dir) {
                        case 1 : 
                            ans.push_back('D');
                            r--;
                            break;
                        case 2 :
                            ans.push_back('U');
                            r++;
                            break;
                        case 3 :
                            ans.push_back('R');
                            c--;
                            break;
                        case 4 :
                            ans.push_back('L');
                            c++;
                            break;
                    }
                    dir = parents[r][c];
                }

                // printAdj(parents);

                break;
            } else {
                parents[r][c] = dir;
                for(int i = 0; i < 4; i++) {
                    int newR = r + dx[i];
                    int newC = c + dy[i];
                    if(newR >= 0 && newR < R && newC >= 0 && newC < C) {
                        q.push({newR,newC,i+1});
                    }
                }
            }
        }
    }
    reverse(ans.begin(),ans.end());
    if(ans.size()) {
        cout << "YES\n" << ans.size() << "\n";
        printV(ans);
    } else {
        cout << "NO\n";
    }

    return 0;
}