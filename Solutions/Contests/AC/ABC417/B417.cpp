#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    map<int,int> a;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x]++;
    }    
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        a[x] = max(0, a[x] - 1);
    }

    for(auto [k, v] : a) {
        for(int i = 0; i < v; i++) cout << k << " ";
    }

    cout << '\n';

    return 0;
}
