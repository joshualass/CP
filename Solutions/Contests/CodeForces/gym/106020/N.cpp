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
    int mx = *max_element(a.begin(), a.end());
    cout << (mx + 2) / 3 << '\n';

    return 0;
}
