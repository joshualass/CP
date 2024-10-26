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
    ld intersectionX(line line2) {
        return (ld) (a - line2.a) / (line2.b - b);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ll a, b, c; cin >> a >> b >> c;

    deque<line> dq;
    dq.push_front({0,0});
    ll sum = 0;
    for(int i = 0; i < n; i++) {
        ll p; cin >> p;
        sum += p;
        while(dq.size() >= 2 && dq[dq.size() - 1].f(sum) <= dq[dq.size() - 2].f(sum)) {
            dq.pop_back();
        }
        line prevline = dq.back();
        ll f = c + 2 * a * sum * sum + prevline.f(sum);
        line nextline = {f, -2 * a * sum};
        while(dq.size() >= 2 && dq[0].intersectionX(dq[1]) >= dq[0].intersectionX(nextline)) {
            dq.pop_front();
        }
        dq.push_front(nextline);
    }

    cout << dq.front().a - a * sum * sum + b * sum << '\n';

    return 0;
}