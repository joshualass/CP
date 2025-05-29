#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

const ld epsilon = 1e-9;
const ld inf = 1e11;

struct vec2 {
    ld x, y;
    vec2() {x = 0, y = 0;}
    vec2(ld _x, ld _y) {x = _x, y = _y;}

    ld length_sq() {
        return x * x + y * y;
    }

    void normalize() {
        ld len = sqrt(length_sq());
        x /= len, y /= len;
    }

    bool operator==(const vec2& other) {
        return x == other.x && y == other.y;
    }
};

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

ld dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

ld cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

ld cross(vec2 a, vec2 b, vec2 c) {
    return cross(sub(b, a), sub(c, a));
}

vec2 mul(vec2 a, ld s){
    return {a.x * s, a.y * s};
}

vec2 div(vec2 a, ld s){
    return {a.x / s, a.y / s};
}

vec2 line_lineIntersect(vec2 s1, vec2 e1, vec2 s2, vec2 e2) {
    ld d = cross((sub(e1, s2)), (sub(e2, s2)));
    // cout << "HERE : " << d << endl;
    if(d == 0) {
        // cout << "PARL" << endl;
        //parl
        return {inf, inf};
    }
    ld p = cross(s2, e1, e2), q = cross(s2, e2, s1);
    // cout << "HERE2" << endl;
    vec2 ans = add(mul(s1, p), mul(e1, q));
    ans = div(ans, d);
    return ans;
}

bool on_segment(vec2 s, vec2 e, vec2 p) {
    ld val = cross(p, s, e);
    ld val2 = dot(sub(s, p), sub(e, p));
    return abs(val) <= epsilon && val2 <= epsilon;
}

vec2 lineseg_isect(vec2 s1, vec2 e1, vec2 s2, vec2 e2) {
    cout << "LINESEG ISECT : " << s1.x << " " << s1.y << endl;
    vec2 isect = line_lineIntersect(s1, e1, s2, e2);
    if(!on_segment(s2, e2, isect)) {
        cout << "NOT ON SEG\n";
        return {inf, inf};
    }
    return isect;
}

int sgn(ld x) {
    if(x < 0) return -1;
    else if(x > 0) return 1;
    return 0;
}

//if p is to the right, returns -1
int sideof(vec2 s, vec2 e, vec2 p) {
    return sgn(cross(s, e, p));
}

signed main() {

    int n, m;
    cin >> n >> m;
    vector<vec2> a(n), b(m);
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    for(int i = 0; i < m; i++){
        ld x, y;
        cin >> x >> y;
        b[i] = {x, y};
    }
    vector<ld> aslen(n);
    for(int i = 0; i < n; i++) aslen[i] = sqrt(sub(a[(i + 1) % n], a[i]).length_sq());
    vector<ld> aspfx(n + 1, 0);
    for(int i = 1; i <= n; i++) aspfx[i] = aspfx[i - 1] + aslen[i - 1];
    //consider b[0] -> b[1] first
    int lptr = -1, rptr = -1;
    // cout << "HERE" << endl;
    for(int i = 0; i < n; i++){
        // cout << "I : " << i << endl;
        vec2 isect = lineseg_isect(b[0], b[1], a[i], a[(i + 1) % n]);
        cout << "ISECT : " << i << " " << isect.x << " " << isect.y << endl;
        if(isect == vec2(inf, inf)) continue;
        int side = sideof(b[0], b[1], a[(i + 1) % n]);
        if(side <= 0) lptr = i;
        else rptr = i;
    }
    cout << "LRPTR : " << lptr << " " << rptr << endl;
    ld ans = 0;
    for(int i = 0; i < m; i++){
        while(true) {
            vec2 isect = lineseg_isect(b[i], b[(i + 1) % m], a[lptr], a[(lptr + 1) % n]);
            if(isect == vec2(inf, inf)) {
                lptr = (lptr + 1) % n;
                continue;
            }
            break;
        }
        while(true) {
            vec2 isect = lineseg_isect(b[i], b[(i + 1) % m], a[rptr], a[(rptr + 1) % n]);
            if(isect == vec2(inf, inf)) {
                rptr = (rptr + 1) % n;
                continue;
            }
            break;
        }
        vec2 bl = b[i], br = b[(i + 1) % m];
        // vec2 ll = a[lptr], a[(lptr + 1) % n];

        cout << "BLINE : " << bl.x << " " << bl.y << " " << br.x << " " << br.y << "\n";
        vec2 li = lineseg_isect(b[i], b[(i + 1) % m], a[lptr], a[(lptr + 1) % n]);
        vec2 ri = lineseg_isect(b[i], b[(i + 1) % m], a[rptr], a[(rptr + 1) % n]);

        cout << "LI RI : " << li.x << " " << li.y << " " << ri.x << " " << ri.y << "\n";
        cout << "LRPTR : " << lptr << " " << rptr << "\n";
        if(rptr != (lptr + 1) % n){
            int l = lptr + 1, r = rptr - 1;
            if(l < r) ans += aspfx[r] - aspfx[l];
            else {
                ans += aspfx[n] - aspfx[l];
                ans += aspfx[r];
            }
        }
        ans += sqrt(sub(li, a[(lptr + 1) % n]).length_sq());
        ans += sqrt(sub(ri, a[rptr]).length_sq());
    }
    ans /= aspfx[n];
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}