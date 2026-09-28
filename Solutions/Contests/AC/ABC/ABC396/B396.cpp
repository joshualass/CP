#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    stack<int> s;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x; cin >> x;
            s.push(x);
        } else {
            int res = 0;
            if(s.size()) {
                res = s.top();
                s.pop();
            }
            cout << res << '\n';
        }
    }    

    return 0;
}