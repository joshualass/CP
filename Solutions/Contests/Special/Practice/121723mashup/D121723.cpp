#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
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

vector<vector<ll>> matexp(vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ll>> result(n,vector<ll>(n));
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    vector<vector<ll>> mat(m,vector<ll>(m));
    for(int i = 1; i < m; i++) {
        mat[i-1][i] = 1;
    }
    mat[m-1][0] = 1;
    mat[m-1][m-1] = 1;

    vector<vector<ll>> res = matexp(mat,n);

    // cout << "res\n" << res;
    cout << res[m-1][m-1] << '\n';

    return 0;
}