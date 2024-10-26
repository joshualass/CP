#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct line {
    ll a, b;
    ll f(ll x) {
        return a + b * x;
    }
    ld intersectionX(line l2) {
        return (ld) (a-l2.a) / (l2.b - b);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    deque<line> dq;
    dq.push_front({0, b[0]});
    for(int i = 1; i < n; i++) {
        while(dq.size() >= 2 && dq[dq.size() - 1].f(a[i]) >= dq[dq.size() - 2].f(a[i])) {
            dq.pop_back();
        }
        line prevline = dq.back();
        ll f = prevline.f(a[i]);
        line nextline = {f, b[i]};
        while(dq.size() >= 2 && dq[0].intersectionX(nextline) <= dq[0].intersectionX(dq[1])) {
            dq.pop_front();
        }
        dq.push_front(nextline);
    }
    cout << dq[0].a << '\n';
    return 0;
}