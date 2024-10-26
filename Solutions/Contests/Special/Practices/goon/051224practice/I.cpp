#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> sizes(n);
    for(int i = 0; i < n - 1; i++) {
        int num; cin >> num;
        num--;
        sizes[num]++;
    }
    vector<int> siblings(1,1);
    for(int x : sizes) {
        if(x) siblings.push_back(x);
    }
    sort(siblings.rbegin(), siblings.rend());

    int l = siblings.size(), r = 2e5;
    while(l != r) {
        int m = (l + r) / 2;
        int infections = 0;
        for(int i = 0; i < siblings.size(); i++) {
            infections += 1 + max(0,siblings[i] - (m - i));
        }    
        if(infections <= m) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}