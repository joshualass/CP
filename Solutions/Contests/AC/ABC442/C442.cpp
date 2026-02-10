#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> cnts(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        cnts[a]++;
        cnts[b]++;
    }

    for(int i = 0; i < n; i++) {
        ll rem = n - 1 - cnts[i];
        if(rem >= 3) {
            cout << rem * (rem - 1) * (rem - 2) / 6;
        } else {
            cout << "0";
        }
        cout << " \n"[i == n - 1];
    }

    return 0;
}
