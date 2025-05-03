#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll euclid(ll a, ll b, ll &x, ll &y) {
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}

void solve() {
    
    ll n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;

    // ll cb = -vx * n, ca = vy * n, c = -vx * y + vy * x;

    // ll g = gcd(gcd(-cb, ca), abs(c));
    // cb /= g; ca /= g, c /= g;

    // if(abs(c) % abs(gcd(cb,ca))) {
    //     cout << "-1\n";
    //     return;
    // }

    // cout << "ca : " << ca << " cb : " << cb << " c : " << c << '\n';
    // ll b = 0, a = 0;

    // ll gg = euclid(ca, cb, a, b);
    // cout << "a : " << a << " b : " << b << '\n';
    // cout << "gg : " << g << '\n';

    // ll ex = cb * b, ey = ca * a;
    // cout << "ex : " << ex << " ey : " << ey << '\n';

    ll ca = n * vy, cb = -vx * n, c = abs(vx * -y + vy * x);
    cout << "ca : " << ca << " cb : " << cb << " c : " << c << '\n';
    ll g = abs(gcd(ca, cb));

    if(abs(c) % g) {
        cout << "-1\n";
        return;
    }

    ll alpha = 0, beta = 0;
    ll res = euclid(ca, cb, alpha, beta);

    alpha = abs(alpha);
    beta = abs(beta);
    ll need = c / g;

    

    ll t = (-x + n * alpha * need) / vx;

    cout << "alpha : " << alpha << " beta : " << beta << " res : " << res << '\n';
    // ll t = (-x + n * alpha) / vx;
    cout << "t : " << t << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}