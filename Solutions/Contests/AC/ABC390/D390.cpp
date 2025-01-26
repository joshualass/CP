#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto nck = [](ll n, ll k) {
        ll res = 1;
        for(int i = 1; i <= n; i++) res *= n;
        for(int i = 1; i <= k; i++) res /= i;
        for(int i = 1; i <= n - k; i++) res /= i;
        return res;
    };

    vector f(13,vector<ll>(13));
    f[0][0] = 1;

    for(int i = 1; i <= 12; i++) {
        for(int j = 1; j <= i; j++) {
            for(int k = 0; k <= i - j; k++) {
                f[i][j] += f[i-j][k] * nck(i,j);
            }
        }
    }

    for(auto ff : f) cout << ff << '\n';

    return 0;
}