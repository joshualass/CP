#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll m, n; cin >> m >> n;
    vector<ll> s(m);
    vector<ll> l(m);
    for(ll &x : s) cin >> x;
    for(ll &x : l) cin >> x;

    /*
    [short -> short, short -> long]
    [long  -> short, long  -> long]
    */
    vector mat(2,vector<ll>(2));

    for(int i = 0; i < m; i++) {
        mat[0][0] = (mat[0][0] + (s[i] + l[i]) * s[i]) % MOD;
        mat[0][1] = (mat[0][1] + (s[i] + l[i]) * l[i]) % MOD;
        mat[1][0] = (mat[1][0] + s[i] * s[i]) % MOD;
        mat[1][1] = (mat[1][1] + s[i] * l[i]) % MOD;
    }

    vector<vector<ll>> start = {{s[0], 0}, {0, l[0]}};
    vector<vector<ll>> end = matexp(start,mat,n-1);

    // cout << "mat\n" << mat;
    // cout << "start\n" << start;
    // cout << "end\n" << end;

    ll res = 0;
    for(int i = 0; i < m; i++) {
        res = (res + (end[0][0] + end[1][0]) * (s[i] + l[i])) % MOD;
        res = (res + (end[0][1] + end[1][1]) * (s[i])) % MOD;
    }

    cout << res << '\n';

    return 0;
}