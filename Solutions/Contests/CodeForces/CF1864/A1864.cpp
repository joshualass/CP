#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int x, y, n; cin >> x >> y >> n;
    vector<int> v(n);
    v[0] = y;
    for(int i = 1; i < n; i++) {
        v[i] = v[i-1] - i;
    }
    if(v[n-1] < x) {
        cout << "-1\n";
    } else {
        v[n-1] = x;
        for(int i = n-1; i >= 0; i--) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}