#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    freopen("buckets.in","r",stdin);
    freopen("buckets.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<vector<char>> v(10, vector<char>(10));
    vector<vector<int>> value(10, vector<int>(10));

    int startR, startC;
    for(int r = 0; r < 10; r++) {
        string line;
        getline(cin, line);
        for(int c = 0; c < 10; c++) {
            v[r][c] = line[c];
            if(line[c] == 'B') {
                startR = r;
                startC = c;
            }
        }
    }

    queue<array<int,3>> q;
    q.push(array<int,3>{startR, startC, 0});
    int ans = -1;
    while(!q.empty()) {
        array<int,3> arr = q.front();
        q.pop();
        int r = arr[0];
        int c = arr[1];
        int step = arr[2];
//        cout << r << " " << c << " " << step << "\n";
        //check in bounds
        if(!(r >= 0 && r <= 9 && c >= 0 && c <= 9)) {
            continue;
        }
        //check rock
        if(v[r][c] == 'R') {
            continue;
        }
        if(v[r][c] == 'L') {
            ans = step - 1;
            break;
        }
        v[r][c] = 'R';
        value[r][c] = step;
        q.push({r+1,c,step+1});
        q.push({r-1,c,step+1});
        q.push({r,c+1,step+1});
        q.push({r,c-1,step+1});
    }
    cout << ans << "\n";

    for(int r = 0; r < 10; r++) {
        for(int c = 0; c < 10; c++) {
 //           cout << v[r][c];
        }
//        cout << "\n";
    }
    return 0;
}