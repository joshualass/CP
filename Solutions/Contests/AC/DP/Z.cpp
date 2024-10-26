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
    ld IntersectionX(line line2) {
        return (ld) (a - line2.a) / (line2.b - b);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c; cin >> n >> c;
    deque<line> dq;
    dq.push_front({0,0});
    ll h;
    for(int i = 0; i < n; i++) {
        cin >> h;
        //find the lowest line from the back
        while(dq.size() >= 2 && dq[dq.size() - 1].f(h) >= dq[dq.size() - 2].f(h)) {
            dq.pop_back();
        }
        ll f = -1;
        if(i == 0) {
            f = h * h;
        } else {
            line prevline = dq.back();
            f = c + h * h * 2 + prevline.f(h);
        }
        line nextline = {f, -2 * h};
        while(dq.size() >= 2 && dq[0].IntersectionX(nextline) <= dq[0].IntersectionX(dq[1])) {
            dq.pop_front();
        }
        dq.push_front(nextline);
    }

    cout << dq.front().a - h * h << '\n';

    return 0;
}