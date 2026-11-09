#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int N = ((int) (2e9)) + 1;


bitset<N> vis {};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> c(10001, 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        while(vis[x * c[x]]) c[x]++;
        cout << x * c[x] << '\n';
        vis[x * c[x]] = 1;
    }

    return 0;
}
