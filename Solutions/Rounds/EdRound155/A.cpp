#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    int a, b; cin >> a >> b;
    bool flag = false;
    for(int i = 0; i < n - 1; i++) {
        int l, r; cin >> l >> r;
        if(l >= a && r >= b) {
            flag = true;
        }
    }
    cout << (flag ? -1 : a) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}