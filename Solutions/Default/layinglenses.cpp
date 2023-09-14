#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<char>> grid(10,vector<char>(10));
    for(int i = 0; i < 10; i++) {
        string word; cin >> word;
        for(int t = 0; t < 10; t++) {
            grid[i][t] = word[t];
        }
    }
    set<char> found;
    for(int i = 0; i < 10; i++) {
        for(int t = 0; t < 10; t++) {
            if(grid[i][t] == '#') {
                break;
            }
            if(grid[i][t] != '.') {
                found.insert(grid[i][t]);
                break;
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int t = 9; t >= 0; t--) {
            if(grid[i][t] == '#') {
                break;
            }
            if(grid[i][t] != '.') {
                found.insert(grid[i][t]);
                break;
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int t = 0; t < 10; t++) {
            if(grid[t][i] == '#') {
                break;
            }
            if(grid[t][i] != '.') {
                found.insert(grid[t][i]);
                break;
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int t = 9; t >= 0; t--) {
            if(grid[t][i] == '#') {
                break;
            }
            if(grid[t][i] != '.') {
                found.insert(grid[t][i]);
                break;
            }
        }
    }
    cout << found.size() << "\n";
    return 0;
}