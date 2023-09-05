#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<vector<ll>> mat(k, vector<ll>(3));

    vector<ll> possible(n);
    possible[0] = 1;

    for (int i = 0; i < k; i++) {
        cin >> mat[i][0] >> mat[i][1];
        mat[i][1]++; // ^__^
    }

    for (int i = 1; i < n; i++) {
        for (int t = 0; t < k; t++) {
            if (i - mat[t][0] >= 0) {
                mat[t][2] = (mat[t][2] + possible[i - mat[t][0]]) % mod;
            }
            if (i - mat[t][1] >= 0) {
                mat[t][2] = (mat[t][2] + mod - possible[i - mat[t][1]]) % mod;
            }
            possible[i] = (possible[i] + mat[t][2]) % mod;
        }
    }

    cout << possible[n - 1] % mod;
    return 0;
}