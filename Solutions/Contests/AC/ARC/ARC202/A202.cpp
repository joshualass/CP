#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e18;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll ops = 0;
    stack<ll> st;

    auto push_stack = [&](ll top) -> void {
        while(st.size() && st.top() == top) {
            st.pop();
            top++;
        }
        st.push(top);
    };

    for(int i = 0; i < n; i++) {
        ll cur = a[i];
        while(st.size() && cur > st.top()) {
            ll top = st.top();
            st.pop();
            ll nx = (st.size() ? st.top() : inf);
            if(nx <= cur) {
                ops += nx - top;
                top += nx - top;
                push_stack(top);
            } else {
                ops += cur - top;
                top += cur - top;
                push_stack(top);
                break;
            }
        }
        push_stack(cur);
    }

    while(st.size() > 1) {
        ll top = st.top();
        st.pop();
        ll nx = st.top();
        ops += nx - top;
        top += nx - top;
        push_stack(top);
    }

    cout << ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}