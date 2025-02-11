#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> s;
    vector<int> a(n);
    int loidx = -1, hiidx = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i] == 1) loidx = i;
        if(a[i] == n) hiidx = i;
        s.insert(a[i]);
    }
    if(s.size() < n) {
        for(int i = 1; i <= n; i++) {
            if(s.count(i) == 0) {
                int j = (i == 1 ? 2 : 1);
                cout << "? " << i << " " << j << endl;
                int res; cin >> res;
                if(res) {
                    cout << "! B" << endl;
                } else {
                    cout << "! A" << endl;
                }
                return;
            }
        }
    } else {
        cout << "? " << loidx + 1 << " " << hiidx + 1 << endl;
        int r0; cin >> r0;
        cout << "? " << hiidx + 1 << " " << loidx + 1 << endl;
        int r1; cin >> r1;
        if(r0 >= n - 1 && r1 >= n - 1) {
            cout << "! B" << endl;
        } else {
            cout << "! A" << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}