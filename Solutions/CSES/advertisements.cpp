#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
suppose current num is greater than stack top
we just push to stack normally, probably should take max
current num is equal, just take max
current nums is less, pop while less than
then take max
all cases, always taking max
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    stack<pair<ll,int>> s;
    ll ans = 0;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        int inserti = i;
        while(s.size() && num <= s.top().first) {
            ans = max(ans, (i - s.top().second) * s.top().first);
            inserti = min(inserti, s.top().second);
            s.pop();
        }
        if(s.empty() || s.size() && num > s.top().first) {
            s.push({num,inserti});
        }
        ans = max(ans, s.top().first * (i - s.top().second + 1));
    }
    while(s.size()) {
        ans = max(ans, (n - s.top().second) * s.top().first);
        s.pop();
    }
    cout << ans << '\n';

    return 0;
}