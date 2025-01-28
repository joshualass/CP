#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct vec2 {
    ld x, y;
    vec2(ld _x = 0, ld _y = 0) {
        x = _x, y = _y;
    }
};

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

ld polar_ang(vec2 a) {
    return atan2(a.y, a.x);
}

ld solve(int pivot, vector<vec2>& a, int n, int m) {
    //sort by polar ang wrt pivot
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }
    ld ans = -1e18;
    for(int i = 0; i < n; i++){
        ans = min(ans, solve(i, a, n, m));
    }
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}