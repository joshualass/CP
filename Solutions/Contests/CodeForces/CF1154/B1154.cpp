#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
    if(sz(a) > 3) {
        cout << "-1\n";
        return 0;
    }
    if(sz(a) == 3) {
        if(a[1] + (a[1] - a[0]) != a[2]) {
            cout << "-1\n";
        } else {
            cout << a[1] - a[0] << '\n';
        }
    } else if(sz(a) == 2) {
        if((a[1] - a[0]) % 2 == 0) {
            cout << (a[1] - a[0]) / 2 << '\n';
        } else {
            cout << a[1] - a[0] << '\n';
        }
    } else {
        cout << 0 << '\n';
    }

    return 0;
}
