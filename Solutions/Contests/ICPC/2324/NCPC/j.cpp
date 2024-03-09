#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    if(m >= n) {
        cout << a[a.size() - 1] << "\n";
        return 0;
    }
    int lptr = n - m - 1;
    int ans = 0;
    for(int i = n - m; i < n; i++){
        int cur = a[i];
        if(lptr >= 0){
            cur += a[lptr --];
        }
        ans = max(ans, cur);
    }
    cout << ans << "\n";

    return 0;
}