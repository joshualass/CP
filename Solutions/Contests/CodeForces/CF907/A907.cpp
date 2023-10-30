#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    
    int n; cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    bool flag = true;

    for(int i = 0; i < n-1; i++) {
        if(__builtin_popcount(i+1) != 1) {
            if(v[i] > v[i+1]) {
                // cout << "false here: " << i  << '\n';
                flag = false;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}