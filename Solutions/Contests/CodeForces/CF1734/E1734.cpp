#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool found;

void recur(int a, vector<vector<int>> &mat, int n) {
    if(a == n * n) {
        bool ok = 1;
        if(ok) {
            // found = 1;
            cout << "solution matrix\n";
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    cout << mat[i][j] << " \n"[j == n - 1];
                }
            }
        }
        return;
    }
    int r = a / n;
    int c = a % n;
    if(r == c) {
        bool ok = 1;
        for(int j = 0; j < r; j++) {
            for(int k = 0; k < c; k++) {
                if((mat[j][k] + mat[r][c]) % n == (mat[j][c] + mat[r][k]) % n) {
                    ok = 0;
                }
            }
        }
        if(ok && !found) recur(a+1,mat,n);
        // recur(a+1,mat,n);
    } else {
        for(int i = 0; i < n; i++) {
            mat[r][c] = i;
            bool ok = 1;
            for(int j = 0; j < r; j++) {
                for(int k = 0; k < c; k++) {
                    if((mat[j][k] + mat[r][c]) % n == (mat[j][c] + mat[r][k]) % n) {
                        ok = 0;
                    }
                }
            }
            if(ok && !found) recur(a+1,mat,n);
        }
    }
}

void test() {
    int n; cin >> n;
    found = 0;
    vector<vector<int>> mat(n,vector<int>(n,-1));
    
    cout << "solutions for v : ";
    for(int i = 0; i < n; i++) {
        cin >> mat[i][i];
        cout << mat[i][i] << " \n"[i == n - 1];
    }
    recur(0,mat,n);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int casi; cin >> casi;
    while(casi--) test();

    return 0;
}