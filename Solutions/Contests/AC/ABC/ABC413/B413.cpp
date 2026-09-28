#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    set<string> s;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) s.insert(a[i] + a[j]);
        }
    }

    cout << s.size() << '\n';

    return 0;
}
