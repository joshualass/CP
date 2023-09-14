#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while(t != 0) {
        int mat[501][501] = {};
        for(int i = 0; i < t; i++) {
            int RR, CC; cin >> RR >> CC;
            int R, C; cin >> R >> C;
            for(int r = RR; r < R; r++) {
                for(int c = CC; c < C; c++) {
                    mat[r][c] = 1;
                }    
            }
        }
        int count = 0;
        for(int r = 0; r <= 500; r++) {
            for(int c = 0; c<= 500; c++) {
                if(mat[r][c]) {
                    count++;
                }
            }
        }
        cout << count << '\n';
        cin >> t;
    }

    return 0;
}