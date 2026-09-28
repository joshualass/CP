#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, l; cin >> n >> l;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num >= l) cnt++;
    }
    cout << cnt << '\n';
    return 0;
}