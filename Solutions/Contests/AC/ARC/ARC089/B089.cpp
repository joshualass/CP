#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector c(2, vector(k, vector<int>(k)));

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        char t; cin >> t;
        int p = (t == 'B' ? 1 : 0);
        //mod each coordinate by 2 * k
        x %= k * 2;
        y %= k * 2;
        //reduce y coordinate to < k
        if(y >= k) {
            y -= k;
            if(x >= k) {
                x -= k;
            } else {
                x += k;
            }
        }
        //reduce x coordinate to < k
        if(x >= k) {
            x -= k;
            p ^= 1;
        }
        //add to counts
        c[p][x][y]++;
    }

    //2-D prefix sum
    vector p(2, vector(k + 1, vector<int>(k + 1)));

    //construct prefix sum with the counts
    for(int i = 0; i < 2; i++) {
        for(int j = 1; j <= k; j++) {
            for(int l = 1; l <= k; l++) {
                p[i][j][l] = p[i][j-1][l] + p[i][j][l-1] - p[i][j-1][l-1] + c[i][j-1][l-1];
            }
        }
    }

    //given color, and coordinates for bottom-left and upper-right of rectangle, count the number of desires in this area with taht color
    auto getareasum = [&](int i, int i1, int j1, int i2, int j2) -> int {
        return p[i][i2][j2] - p[i][i2][j1] - p[i][i1][j2] + p[i][i1][j1];
    };

    int res = 0; //our answer
    for(int i = 0; i < 2; i++) { //iterate through the colors of the squares (2)
        for(int j = 0; j < k; j++) { //iterate through the x-coordinate of the starting square
            for(int l = 0; l < k; l++) { //iterate through the y-coordinate of the starting square
                res = max(res, getareasum(i, 0, 0, j, l) + getareasum(i, j, l, k, k) + getareasum(i ^ 1, 0, l, j, k) + getareasum(i ^ 1, j, 0, k, l)); //add our 4 differnet possible areas
            }
        }
    }

    cout << res << '\n';

    return 0;
}