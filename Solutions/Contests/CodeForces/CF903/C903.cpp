#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<string> mat(n);
    for(auto &x: mat) cin >> x;
    int ops = 0;
    for(int i = 0; i < n / 2; i++) {
        for(int j = 0; j < n / 2; j++) {
            /*
            i,j
            n - i - 1, n - j - 1
            j, n - i - 1
            n - j - 1, i
            */
            char c = max({mat[i][j],mat[n-i-1][n-j-1],mat[j][n-i-1],mat[n-j-1][i]});
            ops += c * 4 - (((int)mat[i][j]) + mat[n-i-1][n-j-1] + mat[j][n-i-1] + mat[n-j-1][i]);
        }
    }
    cout << ops << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}