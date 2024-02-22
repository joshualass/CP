//using binexp
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     ld flip; cin >> flip;
//     ld happy = 1;
//     while(n) {
//         if(n & 1) {
//             happy = happy * (1 - flip) + (1 - happy) * flip;
//         }
//         flip = flip * (1 - flip) + (1 - flip) * flip;
//         n >>= 1;
//     }

//     cout << fixed << setprecision(10) << happy << '\n';

//     return 0;
// }
//using matexp
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<vector<ld>> matmult(vector<vector<ld>> &a, vector<vector<ld>> &b) {
    int n = a.size();
    vector<vector<ld>> res(n,vector<ld>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
            }
            // res[i][j] %= MOD;
        }
    }
    return res;
}

vector<vector<ld>> matexp(vector<vector<ld>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ld>> result(n,vector<ld>(n));
    for(int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    while(pow) {
        if(pow & 1) {
            result = matmult(mat,result);
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n; cin >> n;
    ld p; cin >> p;
    vector<vector<ld>> mat = {{1-p,p},{p,1-p}};
    cout << fixed << setprecision(10) << matexp(mat,n)[0][0] << '\n';

    return 0;
}