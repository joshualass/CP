#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
ld eps = 1e-8;
/*
Notes for stack:
store dimensions of balloon, as well as for what distance it is significant for
From bottom to top of the stack, the distance it's significant should be increasing 

Find insert size
Because the significant distance is increasing in size, we pop elements in the stack until the distance is less than the insertion distance
Then, take min of balloon size and stack thing

Use Geometries to find balloon sizing and distances ft. Marvin

*/

//usaco solution is too clean
//if the current balloon you're on, when you compare it to the top of the stack, if it's larger, then you know you'll never have to compare any balloons
//to the element at the top of the stack so you pop
//if it's smaller than top of stack, just push it there...

ld calc_r(ld dx, ld r1) {
    return dx * dx / 4 / r1;
}

//given that r1 > r2, otherwise we do not care
ld calc_x(ld x1, ld r1, ld x2, ld r2) {
    ld l = x2, r = 1e9 + 1;
    while(r - l > eps) {
        ld m = l + (r - l) / 2;
        ld d1 = calc_r(m - x1, r1);
        ld d2 = calc_r(m - x2, r2);
        if(d1 > d2) {
            l = m;
        } else {
            r = m;
        }
    }
    return l + (r - l) / 2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(3);
    int n; cin >> n;
    stack<pair<ld, pair<ld,ld>>> s; //stored as {significant distance, {x, r}}
    for(int i = 0; i < n; i++) {
        ld x, maxr; cin >> x >> maxr;
        while(s.size() && x > s.top().first) {
            s.pop();
        }
        ld r = min(maxr, s.empty() ? maxr : calc_r(x - s.top().second.first, s.top().second.second));
        //current balloon will always be significant for some portion of graph
        while(s.size() && (r > s.top().second.second || calc_x(s.top().second.first, s.top().second.second, x, r) > s.top().first)) {
            s.pop();
        }
        ld dist = (s.empty() ? 1e9 + 5 : calc_x(s.top().second.first, s.top().second.second, x, r));
        s.push({dist, {x,r}});
        cout << r << '\n';
    }

    return 0;
}