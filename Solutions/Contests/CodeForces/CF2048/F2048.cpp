#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
This solution relies on 2 observations
first, max ops < 64
second, the operations we should consider form a subset tree. For each element an operation, we should include range 
untnil we have a smaller b.
Putting these 2 together, we do a divide and conquer dp approach, with the help of monostack
*/

void solve() {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    stack<pair<array<ll,2>, vector<array<ll,64>>>> st;

    auto mergetwo = [](array<ll,64> a1, array<ll,64> a2) -> array<ll,64> {
        array<ll,64> res = {};
        int p1 = 0, p2 = 0;
        for(int i = 0; i < 64; i++) {
            res[i] = max(a1[p1], a2[p2]);
            if(i != 64 - 1 && a1[p1] < a2[p2]) {
                p2++;
            } else {
                p1++;
            }
        }
        return res;
    };

    auto merger = [&](pair<array<ll,2>, vector<array<ll,64>>> &p) -> array<ll,64> {
        auto [bi, ai] = p.first;

        array<ll,64> cur;
        cur.fill(1);

        while(p.second.size()) {
            cur = mergetwo(p.second.back(), cur);
            p.second.pop_back();
        }

        for(int i = 0; i < 64; i++) {
            cur[i] = max(cur[i], ai);
        }

        array<ll,64> res;
        ll best = cur[0];
        res[0] = best;
        for(int i = 1; i < 64; i++) {   
            best = min(cur[i], (best + bi - 1) / bi);
            res[i] = best;
        }

        return res;

    };

    for(int i = 0; i < n; i++) {
        array<ll,64> add_to_curr = {};
        while(st.size() && st.top().first[0] > b[i]) {
            if(add_to_curr[0]) {
                st.top().second.push_back(add_to_curr);
            }
            add_to_curr = merger(st.top());
            st.pop();
        }
        if(st.size() && st.top().first[0] == b[i]) {
            st.top().first[1] = max(st.top().first[1], a[i]);
        } else {
            st.push({{b[i], a[i]}, {}});
        }
        if(add_to_curr[0]) {
            st.top().second.push_back(add_to_curr);
        }
    }

    array<ll,64> add_to_curr = {};
    while(st.size()) {
        if(add_to_curr[0]) {
            st.top().second.push_back(add_to_curr);
        }
        add_to_curr = merger(st.top());
        st.pop();
    }

    for(int i = 0; i < 64; i++) {
        if(add_to_curr[i] == 1) {
            cout << i << '\n';
            return;
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}