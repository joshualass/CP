#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    map<int,int> cnts;
    vector<int> a(n);
    int clr = -1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = num;
        cnts[num]++;
        if(cnts[num] > 1) clr = num;
    }
    bool used = 0;
    // cout << "clr : " << clr << '\n';
    if(cnts.size() == 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for(int i = 0; i < n; i++) {
            // cout << "i : " << i << " clr : " << clr << " a[i] : " << a[i] << '\n';
            if(used == 0 && (a[i] == clr || clr == -1)) {
                used = 1;
                cout << 'R';
            } else {
                cout << 'B';
            }
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}