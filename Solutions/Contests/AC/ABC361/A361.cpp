#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, x; cin >> n >> k >> x;
    vector<int> a(n);
    for(int &y : a) cin >> y;
    a.insert(a.begin() + k, x);

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
    }

    return 0;
}