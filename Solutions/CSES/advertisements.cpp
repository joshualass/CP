#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
usaco guide problem using stacks
while the stack top is greater than current num, we pop the top of the stack and use the index to insert in as the index of the value we popped
then we push our index if greater than stack (always push unless element of equal value exists)
then we take max area from stack top

after done iterating, take maxes, yea
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