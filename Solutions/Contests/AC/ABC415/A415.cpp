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
    int x; cin >> x;

    cout << (count(a.begin(), a.end(), x) ? "Yes" : "No") << '\n';

    return 0;
}
