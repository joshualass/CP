#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//nt might be the most impossible thing

/*
1
6 1 4 5 2

1
5 1 2 3 1



6 1 4 5 2
5 1 2 3 1

*/

ll euclid(ll a, ll b, ll &x, ll &y) {
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}

struct frac {
    ll n, d;
    frac(ll n, ll d) {
        ll g = gcd(n,d);
        this->n = n / g;
        this->d = d / g;
    }
};

frac operator+(frac lhs, frac rhs) {
    ll n = lhs.n * rhs.d + rhs.n * lhs.d;
    ll d = lhs.d * rhs.d;
    ll g = gcd(n, d);
    // cout << "n : " << n << " d : " << d << " g : " << g << '\n';
    return frac(n / g, d / g);
}

frac operator*(frac lhs, frac rhs) {
    ll n = lhs.n * rhs.n;
    ll d = lhs.d * rhs.d;
    ll g = gcd(n, d);
    // cout << "n : " << n << " d : " << d << " g : " << g << '\n';
    return frac(n / g, d / g);
}

void solve(int ttfang) {
    
    ll n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;

    // if(ttfang == 341) {
    //     cout << "n" << n << "x" << x << "y" << y << "vx" << vx << "vy" << vy << '\n';
    // }

    ll a, b;
    euclid(vy * n, n * vx, a, b);

    if(abs(-y * vx + x * vy) % abs(gcd(vy * n, n * vx))) {
        cout << "-1\n";
        return;
    }

    a *= (-y * vx + x * vy) / gcd(vy * n, n * vx);

    a %= vx / gcd(vx,vy);

    // cout << "a : " << a << '\n';

    frac t(n * a - x, vx);

    ll g = gcd(vx, vy);

    // t.n *= g;
    // t.d *= g;
    // t.n %= n * g;

    // cout << "initial tn : " << t.n << " td : " << t.d << '\n';

    frac mod(n, gcd(vx, vy));
    frac adbc = t * frac(mod.d,mod.n);

    ll sub;

    if(adbc.n >= 0) {
        sub = adbc.n / adbc.d;
    } else {
        sub = -(-adbc.n + adbc.d - 1) / adbc.d;
    }

    frac os = frac(-sub, 1) * mod;

    t = t + os;

    // cout << "tn : " << t.n << " td : " << t.d << '\n';

    ll dx = x + vx * t.n / t.d;
    ll dy = y + vy * t.n / t.d;

    // cout << "dx : " << dx << " dy : " << dy << '\n';

    dx /= n;
    dy /= n;

    // cout << "ndx : " << dx << " ndy : " << dy << '\n';

    ll res = dx - 1 + dy - 1 + (dx + dy) / 2 + abs(dx-dy) / 2;
    cout << res << '\n';    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for(int i = 1; i <= t; i++) solve(i);

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// ll euclid(ll a, ll b, ll &x, ll &y) {
//     if(!b) return x = 1, y = 0, a;
//     ll d = euclid(b, a % b, y, x);
//     return y -= a/b * x, d;
// }

// struct frac {
//     ll n, d;
//     frac(ll n, ll d): n(n), d(d) {}
// };

// frac operator+(frac &lhs, frac &rhs) {
//     ll n = lhs.n * rhs.d + rhs.n * lhs.d;
//     ll d = lhs.d * rhs.d;
//     ll g = gcd(n, d);
//     return frac(n / g, n / d);
// }

// void solve(int ttfang) {
    
//     ll n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;

//     // if(ttfang == 93) {
//     //     cout << "n" << n << "x" << x << "y" << y << "vx" << vx << "vy" << vy << '\n';
//     // }

//     cout << "x : " << x << " vx : " << vx << '\n';
//     cout << "y : " << y << " vy : " << vy << '\n';

//     ll r = -y * vx + x * vy;

//     //no solution
//     if(abs(r) % gcd(abs(n * vy), abs(-n * vx))) {
//         cout << "-1\n";
//         return;
//     }

//     ll a, b;
//     euclid(n * vy, -n * vx, a, b);
//     cout << "a : " << a << " b : " << b << '\n';

//     // cout << "gcd - " << gcd(n * vy, -n * vx) << '\n';

//     ll need = abs(-y * vx + x * vy) / gcd(abs(n * vy), abs(-n * vx));

//     a *= need;
//     b *= need;

//     ll lhs = -x * vy + a * n * vy;
//     ll rhs = -y * vx + b * n * vx;

//     cout << "lhs : " << lhs << " rhs : " << rhs << '\n';

//     ll cn = n, cd = gcd(vx, vy);
//     cout << "cn : " << cn << " cd : " << cd << '\n';
//     ll dn = lhs, dd = vx * vy;
//     cout << "dn : " << dn << " dd : " << dd << '\n';
    
//     frac c = frac(n, gcd(vx,vy));
//     frac d = frac(lhs, vx * vy);

//     if(d.n < 0) {
//         d = d + c;
//     }

//     ll dx = x + vx * d.n / d.d;
//     ll dy = y + vy * d.n / d.d;

//     cout << "dx : " << dx << " dy : " << dy << '\n';

//     dx /= n;
//     dy /= n;

//     cout << "ndx : " << dx << " ndy : " << dy << '\n';

//     ll res = dx - 1 + dy - 1 + (dx + dy) / 2 + abs(dx-dy) / 2;
//     cout << res << '\n';

//     // ll cb = -vx * n, ca = vy * n, c = -vx * y + vy * x;

//     // ll g = gcd(gcd(-cb, ca), abs(c));
//     // cb /= g; ca /= g, c /= g;

//     // if(abs(c) % abs(gcd(cb,ca))) {
//     //     cout << "-1\n";
//     //     return;
//     // }

//     // cout << "ca : " << ca << " cb : " << cb << " c : " << c << '\n';
//     // ll b = 0, a = 0;

//     // ll gg = euclid(ca, cb, a, b);
//     // cout << "a : " << a << " b : " << b << '\n';
//     // cout << "gg : " << g << '\n';

//     // ll ex = cb * b, ey = ca * a;
//     // cout << "ex : " << ex << " ey : " << ey << '\n';

//     // ll ca = n * vy, cb = -vx * n, c = abs(vx * -y + vy * x);
//     // cout << "ca : " << ca << " cb : " << cb << " c : " << c << '\n';
//     // ll g = abs(gcd(ca, cb));

//     // if(abs(c) % g) {
//     //     cout << "-1\n";
//     //     return;
//     // }

//     // ll alpha = 0, beta = 0;
//     // ll res = euclid(ca, cb, alpha, beta);

//     // alpha = abs(alpha);
//     // beta = abs(beta);
//     // ll need = c / g;

    

//     // ll t = (-x + n * alpha * need) / vx;

//     // cout << "alpha : " << alpha << " beta : " << beta << " res : " << res << '\n';
//     // // ll t = (-x + n * alpha) / vx;
//     // cout << "t : " << t << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int t; cin >> t;
//     for(int i = 1; i <= t; i++) solve(i);

//     return 0;
// }