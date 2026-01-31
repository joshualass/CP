#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a;
    for(int l = 1, r = n; l <= r; ) {
        a.push_back(l++);
        if(l <= r) a.push_back(r--);
    }
    reverse(a.begin(), a.end());
    for(int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}