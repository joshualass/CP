#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 4294967296;

int dx [8] = {1,1,-1,-1,2,2,-2,-2};
int dy [8] = {2,-2,2,-2,1,-1,1,-1};

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

vector<vector<ll>> matmult(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> res(n,vector<ll>(n));
    // cout << "a : \n" << a;
    // cout << "b : \n" << b;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
                res[i][j] &= 4294967295;
            }
        }
    }
    // cout << "res ? \n" << res;
    return res;
}

vector<vector<ll>> matexp(vector<vector<ll>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ll>> result(n,vector<ll>(n));
    result[0][0] = 1; //starting out, there is only 1 way to start and end at 

    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat);
        }
        mat = matmult(mat,mat);
        // cout << "updmat?\n" << mat;
        pow >>= 1;
    }
    return result;
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll k; cin >> k;
    vector<vector<ll>> mat(65,vector<ll>(65));
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            for(int k = 0; k < 8; k++) {
                int ax = i + dx[k];
                int ay = j + dy[k];
                if(ax >= 0 && ax < 8 && ay >= 0 && ay < 8) {
                    mat[i * 8 + j][ax * 8 + ay] = 1;
                }
            }
        }
    }
    for(int i = 0; i < 65; i++) {
        mat[i][64] = 1;
    }

    vector<vector<ll>> res = matexp(mat,k);

    // cout << "mat\n" << mat;
    // cout << "res\n" << res;

    ll ans = 0;
    for(int i = 0; i < 65; i++) {
        for(int j = 0; j < 65; j++) {
            ans += res[i][j];
            ans &= 4294967295;
        }
    }
    cout << ans << '\n';
    // cout << reduce(res[64].begin(), res[64].end()) << '\n';

    return 0;
}