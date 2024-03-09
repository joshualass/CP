#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> v(n);
    for(int &x : v) cin >> x;

    int most = *max_element(v.begin(),v.end());
    vector<bool> found(most + 1);

    for(int x : v) {
        found[x] = 1;
    }
    bool ok = 1;
    for(int i = 1; i <= most; i++) {
        if(!found[i]) {
            ok = 0;
            cout << i << '\n';
        }
    }
    if(ok) {
        cout << "good job\n";
    }

    return 0;
}