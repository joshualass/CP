#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    stack<array<int,2>> st;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        while(st.size() && st.top()[0] < x) st.pop();
        if(st.size() && st.top()[0] == x) {
            res += i - st.top()[1] - 1;
        }
        st.push({x,i});
    }

    cout << res << '\n';

    return 0;
}