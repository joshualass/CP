#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    
    cout << (accumulate(a.begin(), a.end(), 0) <= m ? "Yes" : "No") << '\n';

    return 0;
}
