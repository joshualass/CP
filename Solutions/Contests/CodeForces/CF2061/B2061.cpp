#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    set<int> vis;
    vector<int> a(n);
    int maxdup = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(vis.count(a[i])) {
            maxdup = max(maxdup,a[i]);
        }
        vis.insert(a[i]);
    }
    sort(a.begin(),a.end());
    int r = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(r < 2 && a[i] == maxdup) {
            a.erase(a.begin() + i);
            r++;
        }
    }

    for(int i = 1; i < a.size(); i++) {
        if(a[i] - a[i-1] < maxdup * 2) {
            cout << maxdup << " " << maxdup << " " << a[i]<< " " << a[i-1] << '\n';
            return;
        }
    }

    cout << "-1\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}