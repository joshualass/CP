#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }

    vector<int> a(s.begin(), s.end());
    cout << a.size() << '\n';
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
    }

    // for(int x : s) cout << x << " ";
    // cout << '\n';

    return 0;
}
