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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;
    vector<vector<char>> mat(n,vector<char>(m,'.'));
    for(int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        mat[a][b] = '#';
    }

    cout << mat << '\n';

    return 0;
}