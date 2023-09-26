#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e3;

int prefix[N+1][N+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    for(int i = 0; i <= n; i++) {
        prefix[i][0] = 0;
        prefix[0][i] = 0;
    }
    vector<string> v(n);
    for(auto &x: v) cin >> x;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + (v[i-1][j-1] == '*' ? 1 : 0);
            // cout << prefix[i][j] << " ";
        }
        // cout << "\n";
    }
    for(int i = 0; i < q; i++) {
        int a, b, c, d; cin >> c >> d >> a >> b;
        cout << prefix[a][b] - prefix[c-1][b] - prefix[a][d-1] + prefix[c-1][d-1] << "\n";
    }

    return 0;
}