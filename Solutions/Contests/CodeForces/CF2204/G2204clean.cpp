#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
ll MOD;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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
vector<vector<ll>> matexp(vector<vector<ll>> result, vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

int debug = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m >> MOD;
    vector<vector<ll>>base(m + 1, vector<ll>(m + 1)), mat(m + 1, vector<ll>(m + 1));
    base[0][0] = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            mat[i][j] = (m - max(i,j) + mat[i][j]) % MOD;
            if(j < i) {
                mat[i][m-j-1] = ((i - m + mat[i][m-j-1]) % MOD + MOD) % MOD;
            }
        }
        mat[i][m] = (m - i) % MOD;
    }

    mat[m][m] = 1;

    auto res = matexp(base, mat, n);
    cout << res[0][m] << '\n';

    return 0;
}
