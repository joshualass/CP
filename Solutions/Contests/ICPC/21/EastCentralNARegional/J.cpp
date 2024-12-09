#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    stack<array<ll,2>> st; //{index, length}

    array<ll,3> res = {-1,-1,-1};

    auto ckmax = [&](array<ll,3> a) -> void {
        if(a[2] > res[2] || a[2] == res[2] && a[0] < res[0]) {
            res = a;
        }
    };
    
    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        array<ll,2> add = {i,x};
        while(st.size() && st.top()[1] > x) {
            array<ll,2> prev = st.top();
            st.pop();
            array<ll,3> t = {prev[0], i, (i-prev[0])*prev[1]};
            ckmax(t);
            add[0] = prev[0];
        }
        st.push(add);
    }

    while(st.size()) {
        array<ll,2> prev = st.top();
        array<ll,3> t = {prev[0],n,(n-prev[0])*prev[1]};
        ckmax(t);
        st.pop();
    }

    cout << res[0] + 1 << " " << res[1] << " " << res[2] << '\n';    

    return 0;
}