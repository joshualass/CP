#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll MOD = 1e9 + 7;

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
                res[i][j] %= MOD;
            }
        }
    }
    return res;
}
//use notation of [from][to]
vector<vector<ll>> matexp(int n, vector<vector<ll>> mat, vector<vector<ll>> result, ll pow) {

    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
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
    vector<vector<ll>> a(4, vector<ll>(4));
    a[0][0] = 1;
    vector<vector<ll>> b(4, vector<ll>(4));
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i - j) {
                b[i][j] = 1;
            }
        }
    }

    auto res = matexp(4, b, a, n);

    cout << res[0][0] << '\n';

    return 0;
}
