#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    ll res = 1;

    stack<array<ll,2>> s; // stores {sum of attacks of group, attack of rightmost group}

    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        array<ll,2> t = {x, x};

        while(s.size() && s.top()[0] <= t[1]) {
            array<ll,2> a = s.top();
            s.pop();
            ll left_merge_res = (s.size() ? (s.top()[1] + a[0]) / a[0] : LLONG_MAX);
            ll right_merge_res = (x + a[0]) / a[0];
            if(left_merge_res < right_merge_res) {
                array<ll,2> prevtop = s.top();
                s.pop();
                prevtop = {prevtop[0] + a[0], a[1]};
                s.push(prevtop);
            } else {
                t[0] += a[0];
            }
            res = max(res, min(left_merge_res, right_merge_res));
        }

        s.push(t);

    }

    while(s.size() > 1) {
        array<ll,2> a = s.top();
        s.pop();
        ll left_merge_res = (s.size() ? (s.top()[1] + a[0]) / a[0] : LLONG_MAX);
        array<ll,2> prevtop = s.top();
        s.pop();
        prevtop = {prevtop[0] + a[0], a[1]};
        s.push(prevtop);
        res = max(res, left_merge_res);
    }

    cout << res << '\n';

    return 0;
}
