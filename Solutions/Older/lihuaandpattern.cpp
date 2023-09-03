#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, k; cin >> n >> k;
        vector<vector<int>> mat(n,vector<int>(n));
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                cin>> mat[r][c];
            }
        }
        int ops = 0;
        for(int r = 0; r < (n + 1) / 2; r++) {
            for(int c = 0; c < n; c++) {
                if(r * 2 == n - 1) {
                    if(c >= n /2) {
                        continue;
                    }
                }
                 if(mat[r][c] != mat[n-r-1][n-c-1]) {
                    ops++;
                    // cout << r << " " << c << "\n";
                 }
            }
        }
        // cout << ops << "\n";
        if(ops > k || n % 2 == 0 && (k % 2 != ops % 2) || n % 2 == 1 && k == ops && (k % 2 != ops % 2)) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
        // cout << ((ops > k || k % 2 != ops % 2) ? "NO" : "YES") << "\n";
    }

    return 0;
}