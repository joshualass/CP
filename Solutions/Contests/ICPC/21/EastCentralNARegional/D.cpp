#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct vec2 {
    ld x, y;
    vec2() {}
    vec2(ld _x, ld _y) {
        x = _x, y = _y;
    }
};

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

ld dist_sq(vec2 a, vec2 b) {
    ld dx = a.x - b.x;
    ld dy = a.y - b.y;
    return dx * dx + dy * dy;
}

ld dist(vec2 a, vec2 b) {
    return sqrt(dist_sq(a, b));
}

vec2 mul(vec2 a, ld s) {
    return {a.x * s, a.y * s};
}

ld cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld tri_area(vec2 t1, vec2 t2, vec2 t3) {
    vec2 d1 = sub(t2, t1);
    vec2 d2 = sub(t3, t1);
    return cross(d1, d2) / 2.0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vec2 o;
    cin >> o.x >> o.y;
    ld r;
    cin >> r;
    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    for(int i = 0; i < n; i++){
        a[i] = sub(a[i], o);
    }
    int N = 100000;
    ld ans = 0;
    for(int i = 0; i < n; i++){
        vec2 s = a[i];
        vec2 t = a[(i + 1) % n];
        vec2 dir = sub(t, s);
        for(int j = 0; j < N; j++){
            vec2 u = add(s, mul(dir, (ld) (j) / (ld) (N)));
            vec2 v = add(s, mul(dir, (ld) (j + 1) / (ld) (N)));
            ld ul = 
            ans += tri_area(u, v, vec2(0, 0));
        }
    }
    ans = abs(ans);
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}