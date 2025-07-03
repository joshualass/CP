#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) {
        cin >> x;
        x--;
    }

    set<int> sa, sb;
    for(int i = 0; i < n; i++) sa.insert(i), sb.insert(i);

    vector<int> aa(n,-1), ab(n,-1);

    int ok = 1;

    auto dfs = [&](auto self, int i, int j) -> void {

        if(j == 0) {
            int idx = aa[i], val = b[i];
            if(ab[idx] == -1) {
                ab[idx] = val;
                sb.erase(val);
                self(self, idx, 1);
            } else if(ab[idx] != val) {
                ok = 0;
            }
        } else {
            int idx = ab[i], val = a[i];
            if(aa[idx] == -1) {
                aa[idx] = val;
                sa.erase(val);
                self(self, idx, 0);
            } else if(aa[idx] != val) {
                ok = 0;
            }
        }

    };

    for(int i = 0; i < n; i++) {
        if(aa[i] == -1) {
            aa[i] = *sa.begin();
            sa.erase(sa.begin());
            dfs(dfs, i, 0);
        }
    }

    if(ok) {
        cout << "YES\n";
        for(int i = 0; i < n; i++) cout << aa[i] + 1 << " \n"[i == n - 1];
        for(int i = 0; i < n; i++) cout << ab[i] + 1 << " \n"[i == n - 1];
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}