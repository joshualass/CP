#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> a(8);
    for(auto &x : a) cin >> x;
    vector<int>b(8,1), c(8,1);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(a[i][j] == '#') {
                b[i] = 0;
                c[j] = 0;
            }
        }
    }

    cout << (reduce(b.begin(),b.end()) * reduce(c.begin(),c.end())) << '\n';

    return 0;
}