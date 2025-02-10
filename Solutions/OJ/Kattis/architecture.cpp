#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    cout << (*max_element(a.begin(),a.end()) == *max_element(b.begin(),b.end()) ? "possible" : "impossible") << '\n';

    return 0;
}   