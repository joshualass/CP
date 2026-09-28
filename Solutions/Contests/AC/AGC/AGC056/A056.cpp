#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int t = n;
    vector<vector<char>> a(n,vector<char>(n,'.'));

    priority_queue<array<int,3>> pq;

    int r = 0;
    while(n % 3) {
        pq.push({2,4,r});
        r += 4;
        n -= 4;
    }

    while(n) {
        pq.push({3,3,r});
        r += 3;
        n -= 3;
    }

    int c = 0;
    while(pq.size()) {
        auto [left, len, r] = pq.top();
        pq.pop();
        if(len == 4) {
            if(left == 2) {
                /*
                Block of shape
                #.
                .#
                ##
                ##
                */
                a[r][c] = '#';
                a[r+1][c+1] = '#';
                a[r+2][c] = '#';
                a[r+2][c+1] = '#';
                a[r+3][c] = '#';
                a[r+3][c+1] = '#';
            } else {
                /*
                block of shape
                ##
                ##
                #.
                .#
                */
                a[r][c] = '#';
                a[r][c+1] = '#';
                a[r+1][c] = '#';
                a[r+1][c+1] = '#';
                a[r+2][c] = '#';
                a[r+3][c+1] = '#';
            }
            c += 2;
        } else {
            a[r][c] = '#';
            a[r+1][c] = '#';
            a[r+2][c] = '#';
            c++;
        }

        left--;
        if(left) {
            pq.push({left, len, r});
        }
    }

    for(int i = 0; i < t; i++) {
        for(int j = 0; j < t; j++) {
            cout << a[i][j];
        }
        cout << '\n';
    }

    return 0;
}