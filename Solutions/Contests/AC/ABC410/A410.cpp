#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int k; cin >> k;
    int res = 0;
    for(int x : a) if(k <= x) res ++;

    cout << res << '\n';

    return 0;
}
