#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    if(n %  2 == 0) {
        cout << "-1\n";
        return;
    }   
    int c = 1;
    vector<int> p(n);
    for(int i = 0; i < n / 2; i++) {
        p[i] = c++;
    }
    for(int i = n - 1; i >= n / 2; i--) {
        p[i] = c++;
    }
    for(int i = 0; i < n; i++) {
        cout << p[i] << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}