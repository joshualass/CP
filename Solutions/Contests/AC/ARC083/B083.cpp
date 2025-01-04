#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    
    vector mat(n, vector<int>(n));
    for(auto &x : mat) for(auto &y : x) cin >> y;

    ll res = 0;

    //iterate over all pairs of nodes i, j
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int found_equal_path = 0;
            for(int k = 0; k < n; k++) {
                //if shorter, than graph is impossible to construct
                if(mat[i][k] + mat[k][j] < mat[i][j]) {
                    cout << "-1\n";
                    return 0;
                }
                //chekc if equal path found
                if(mat[i][k] + mat[k][j] == mat[i][j] && k != i && k != j) {
                    found_equal_path = 1;
                }
            }
            //if equal path found, exclude
            if(found_equal_path == 0) {
                res += mat[i][j];
            }
        }
    }
    
    //divide by 2 as to not double count the edges going in both directions
    cout << res / 2 << '\n';

    return 0;
}