#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int res = 0;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        int cnt = 0;
        for(int j = 0; j < k; j++) {
            int num; cin >> num;
            if(s.find(num) == s.end()) {
                cnt++;
            }
            s.insert(num);
        }
        res = max(res,cnt);
    }
    cout << res << '\n';
    return 0;
}