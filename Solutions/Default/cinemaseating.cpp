#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;

    int n;
    cin >> n;

    vector<vector<bool>> v(R, vector<bool>(C, 0));

    for(int i = 0; i < n; i++) {

            int row, col;
            cin >> row >> col;
            v[row - 1][col - 1] = true;
    }

    vector<int> seats(9, 0);

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int count = 0;
            if(v[r][c]) {

            if (r != 0) {
                if (c != 0) {
                    if (v[r - 1][c - 1]) {
                        count++;
                    }
                }
                if (v[r - 1][c]) {
                    count++;
                }
                if (c != C - 1) {
                    if (v[r - 1][c + 1]) {
                        count++;
                    }
                }
            }
            if (c != 0 && v[r][c - 1]) {
                count++;
            }
            if (c != C - 1 && v[r][c + 1]) {
                count++;
            }
            if (r != R - 1) {
                if (c != 0) {
                    if (v[r + 1][c - 1]) {
                        count++;
                    }
                }
                if (v[r + 1][c]) {
                    count++;
                }
                if(c != C-1) {
                    if(v[r+1][c+1]) {
                        count++;
                    }
                }
            }
            seats[count]++;
            }
        }
    }
    for(int i = 0; i < 9; i++) {
        cout << seats[i] << ' ';
    }

    return 0;
}