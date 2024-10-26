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
    ld X_Intersection(line line2) {
        return (ld) (a - line2.a) / (line2.b - b);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,3>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    sort(a.begin(), a.end()); //sort by increasing x

    ll ans = 0;
    deque<line> dqlines;
    dqlines.push_front({0,0});
    for(int i = 0; i < n; i++) {
        auto [currx, curry, ai] = a[i];
        //querying at point y. 
        while(dqlines.size() >= 2 && dqlines[dqlines.size() - 1].f(curry) <= dqlines[dqlines.size() - 2].f(curry)) {
            dqlines.pop_back();
        }
        line bestprev = dqlines.back();
        ll f = currx * curry - ai + bestprev.f(curry);
        ans = max(ans, f);
        line nextline = {f, -currx};
        while(dqlines.size() >= 2 && dqlines[0].X_Intersection(dqlines[1]) <= dqlines[0].X_Intersection(nextline)) {
            dqlines.pop_front();
        }
        dqlines.push_front(nextline);
    }
    cout << ans << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// struct Rect {
//     ll p, q, a;
// };

// struct line {
//     long long m, c;
//     long long eval(long long x) { return m * x + c; }
//     long double intersectX(line l) { return (long double) (c - l.c) / (l.m - m); }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<Rect> rects(n+1);

//     for(int i = 1; i <= n; i++) {
//         cin >> rects[i].p >> rects[i].q >> rects[i].a;
//     }

//     sort(rects.begin(), rects.end(), [](const auto &lhs, const auto &rhs) {
//         return lhs.p < rhs.p;
//     });

//     deque<line> dq;
//     dq.push_front({0, 0});
//     long long ans = 0;
//     for (int i = 1; i <= n; i++) {
//         while (dq.size() >= 2 && dq.back().eval(rects[i].q) <= dq[dq.size() - 2].eval(rects[i].q)) {
//             cout << "popping line from back c : " << dq.back().c << " m : " << dq.back().m << '\n';
//             dq.pop_back();
//         }
//         long long f = dq.back().eval(rects[i].q) + rects[i].p * 1LL * rects[i].q - rects[i].a;
//         ans = max(ans, f);
//         line cur = {-rects[i].p, f};
//         cout << "i : " << i << " f : " << f << " m : " << -rects[i].p << '\n';
//         while (dq.size() >= 2 && cur.intersectX(dq[0]) >= dq[0].intersectX(dq[1])){
//             cout << "popping line from front c : " << dq.front().c << " m : " << dq.front().m << '\n';
//             dq.pop_front();
//         }
//         dq.push_front(cur);
//     }

//     return 0;
// }
