#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<string> construct(int steps) {
    
    //impossible to completei n in an even number of steps due to parity
    if(steps % 2 == 0) return {};

    steps--;
    int r = min(49, steps / 2), c = min(50, steps / 2 + 1);
    if(r * 2 % 4 != steps % 4) {
        r--;
        c--;
    }

    vector<string> maze(r,string(c, '.'));

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(j > i + 1) {
                if((i + j) & 1) {
                    maze[i][j] = '\\';
                } else {
                    maze[i][j] = '/';
                }
            } else if(i > j) {
                if((i + j) & 1) {
                    maze[i][j] = '/';
                } else {
                    maze[i][j] = '\\';
                }
            } else {
                maze[i][j] = '\\';
            }
        }
    }

    steps -= r * 2;

    for(int i = 1; i < r - 1; i++) {
        for(int x = i, y = i + 1; x > 0 && y < c - 1; x--, y++) {
            if(steps) {
                maze[x][y] = '/';
                steps -= 4;
            }
        }
    }

    for(int i = 1; i < r - 1; i++) {
        for(int x = i, y = i; x < r - 1 && y > 0; x++, y--) {
            if(steps) {
                maze[x][y] = '/';
                steps -= 4;
            }
        }
    }

    return maze;

}

/*
down, up, right, left
0, 1, 2, 3
*/

int find_path_length(vector<string> a) {

    // for(auto &x : a) cout << x << endl;

    // return 0;

    int steps = 1;
    int cx = 0, cy = 0;

    int prev = 0;
    
    // cout << "cx : " << cx << " cy : " << cy << endl;


    while(cx != a.size() || cy != a[0].size() - 1) {
        // cout << "cx : " << cx << " cy : " << cy << endl;
        steps++;
        if(prev == 0) {
            if(a[cx][cy] == '\\') {
                cy++;
                prev = 2;
            } else {
                cy--;
                prev = 3;
            }
        } else if(prev == 1) {
            if(a[cx][cy] == '\\') {
                cy--;
                prev = 3;
            } else {
                cy++;
                prev = 2;
            }
        } else if(prev == 2) {
            if(a[cx][cy] == '\\') {
                cx++;
                prev = 0;
            } else {
                cx--;
                prev = 1;
            }
        } else {
            if(a[cx][cy] == '\\') {
                cx--;
                prev = 1;
            } else {
                cx++;
                prev = 0;
            }
        }

    }
    return steps;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 1; i <= 3000; i++) {
    //     if((i & 1) && i >= 3) {
    //         cout << "i : " << i << " path length : " << find_path_length(construct(i)) << '\n';
    //         //check all equal. 
    //         assert(find_path_length(construct(i)) == i);
    //     } else {
    //         cout << "i : " << i << " not possible\n";
    //     }
    // }

    vector<string> a;
    for(int i = 0; i < 48; i++) {
        string s; cin >> s;
        a.push_back(s);
    }

    cout << find_path_length(a) << '\n';

    return 0;
}