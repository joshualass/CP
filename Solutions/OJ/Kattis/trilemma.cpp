#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ld eps = 1e-8;
ld PI = acos(-1);

template<class F>
struct Point {
    F x, y;
    Point(): x(0), y(0) {}
    Point(const F& x, const F& y): x(x), y(y) {}

    void swap(Point& other) {
        swap(x, other.x);
        swap(y, other.y);
    }

    template <class F1> explicit operator Point<F1> () {
        return Point<F1>(static_cast<F1>(x), static_cast<F1>(y));
    }

    template <class F1> Point& operator=(const Point<F1>& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    template <class F1> Point& operator +=(const Point<F1>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    template<class F1> Point& operator -=(const Point<F1>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template<class F1> Point& operator *=(const F1& factor) {
        x *= factor;
        y *= factor;
        return *this;
    }

    template<class F1> Point& operator /= (const F1& factor) {
        x /= factor;
        y /= factor;
        return *this;
    }

};

template <class F> istream& operator >>(istream& is, Point<F>& point) {
    return is >> point.x >> point.y;
}

template <class F> ostream& operator <<(ostream& os, const Point<F>& point) {
    return os << point.x << ' ' << point.y;
}

template <class F> inline Point<F> makePoint(const F& x, const F& y) {
    return Point<F>(x, y);
}

template <class F> void swap(Point<F>& lhs, Point<F>& rhs) {
    lhs.swap(rhs);
}

template <class F> inline auto operator -(Point<F>& point) {
    return makePoint(-point.x, -point.y);
}

template <class F1, class F2> inline auto operator +(Point<F1>& lhs, Point<F2>& rhs) {
    return makePoint(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <class F1, class F2> inline auto operator -(Point<F1>& lhs, Point<F2>& rhs) {
    return makePoint(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <class F1, class F2> inline auto operator *(F1& factor, Point<F2>& rhs) {
    return makePoint(factor * rhs.x, factor * rhs.y);
}

template <class F1, class F2> inline auto operator *(Point<F1>& lhs, F2& factor) {
    return makePoint(factor * lhs.x, factor * lhs.y);
}

template <class F1, class F2> inline auto operator /(Point<F1>& lhs, F2& factor) {
    return makePoint(lhs.x / factor, lhs.y / factor);
}

//dot product
template <class F1, class F2> inline auto operator *(Point<F1>& lhs, Point<F2>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

//determinant / cross product 
template <class F1, class F2> inline auto operator ^(Point<F1>& lhs, Point<F2>& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}


//ccw functions which I don't know what they do
template <class F1, class F2> inline auto ccw(Point<F1>& lhs, Point<F2>& rhs) {
    return rhs ^ lhs;
}

template <class F1, class F2, class F3> inline auto ccw(Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin) {
    return ccw(lhs - origin, rhs - origin);
}

//comparison operators
template <class F1, class F2> inline auto operator ==(Point<F1>& lhs, Point<F2>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
    /*with error
    ld epsilon = 1E-10;
    return (abs(lhs.x - rhs.x) < epsilon && abs(lhs.y - rhs.y) < episilon);
    */
}

template <class F1, class F2> inline auto operator !=(Point<F1>& lhs, Point<F2>& rhs) {
    return !(lhs == rhs);
}

template <class F1, class F2> inline auto operator <(Point<F1>& lhs, Point<F2>& rhs) {
    lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

template <class F1, class F2> inline auto operator >(Point<F1>& lhs, Point<F2>& rhs) {
    return rhs < lhs;
}

template <class F1, class F2> inline auto operator <=(Point<F1>& lhs, Point<F2>& rhs) {
    return !(lhs > rhs);
}

template <class F1, class F2> inline auto operator >=(Point<F1>& lhs, Point<F2>& rhs) {
    return !(lhs < rhs);
}

//angles and rotations (counter-clockwise)
template <class F> inline auto angle(Point<F>& point) {
    return atan2(point.y, point.x);
}

template <class F1, class F2> inline auto angle(Point<F1>& lhs, Point<F2>& rhs) {
    return atan2(lhs ^ rhs, lhs * rhs);
}

ld angle(Point<ld> p1, Point<ld> p2) {
    return atan2(p1 ^ p2, p1 * p2);
}

ld angle(Point<ld> p1, Point<ld> p2, Point<ld> p3) {
    return angle(p1 - p3, p2 - p3);
}

// template <class F1, class F2, class F3> inline auto angle(Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin) {
//     return angle(lhs - origin, rhs - origin);
// }

template <class F1, class F2, class F3> inline auto rotate(Point<F1>& point, Point<F2>& angleSin, Point<F3>& angleCos) {
    return makePoint(angleCos * point.x - angleSin * point.y,
                     angleSin * point.x + angleCos * point.y
    );
}

template <class F1, class F2> inline auto angle(Point<F1>& lhs, F2& angle) {
    return rotate(lhs, sin(angle), cos(angle));
}

template <class F1, class F2, class F3> inline auto rotate(Point<F1>& point, F2& angle, Point<F3>& origin) {
    return origin + rotate(point - origin, angle);
}

template <class F> inline auto perp(Point<F>& point) {
    return makePoint(-point.y, point.x);
}

// distances
template <class F> inline auto abs(Point<F>& point) {
    return point * point;
}

//normal distance
template <class F> inline auto norm(Point<F>& point) {
    return sqrt(abs(point));
}

ld calcdist(Point<ld> p1, Point<ld> p2) {
    Point<ld> p = p1 - p2;

    return p.x * p.x + p.y * p.y;

}

//normal distance
template <class F1, class F2> inline auto dist(Point<F1>& lhs, Point<F2>& rhs) {
    return norm(lhs - rhs);
}

template <class F1, class F2> inline auto dist2(Point<F1>& lhs, Point<F2>& rhs) {
    return abs(lhs - rhs);
}

template <class F1, class F2> inline auto bisector(Point<F1>& lhs, Point<F2>& rhs) {
    return lhs * norm(rhs) + rhs * norm(lhs);
}

void solve() {

    ld a,b,c,d,e,f; cin >> a >> b >> c >> d >> e >> f;
    set<pair<int,int>> s;
    s.insert({a,b});
    s.insert({c,d});
    s.insert({e,f});
    if(s.size() != 3) {
        cout << "not a triangle\n";
        return;
    }
    Point<ld> p1(a,b);
    Point<ld> p2(c,d);
    Point<ld> p3(e,f);

    angle(p1,p2,p3);

    // cout << "angle ? " << angle(p1,p2,p3) << '\n';

    vector<ld> v;
    // v.push_back(angle(p1,p2,p3));
    v.push_back(angle(p1,p3,p2));
    v.push_back(angle(p1,p2,p3));
    v.push_back(angle(p2,p1,p3));
    v.push_back(angle(p2,p3,p1));
    v.push_back(angle(p3,p1,p2));
    v.push_back(angle(p3,p2,p1));

    bool haslinear = 0;
    int hasobteuse = 0;
    bool hasright = 0;
    bool iso = 0;
    for(auto a : v) {
        // cout << "a : " << a << '\n';
        if(abs(a) < eps || abs(a-PI) < eps) {
            haslinear = 1;
        }
        if(abs(a - PI/2) < eps) {
            hasright = 1;
        }
        if(abs(a)> PI/2 + eps) {
            hasobteuse++;
        }
    }

    if(haslinear) {
        cout << "not a triangle\n";
        return;
    }

    ll l1 = calcdist(p1,p2);
    ll l2 = calcdist(p2,p3);
    ll l3 = calcdist(p3,p1);

    // cout << "l1 : " << l1 << " l2 : " << l2 << " l3 : " << l3 << '\n';

    if(abs(l1 - l2) < eps || abs(l2-l3) < eps || abs(l3-l1) < eps) {
        iso = 1;
    }

    if(iso) {
        cout << "isosceles ";
    } else {
        cout << "scalene ";
    }
    // cout << "hasobtuse ? " << hasobteuse << '\n';
    if(hasobteuse == 2) {
        cout << "obtuse ";
    } else if(hasright) {
        cout << "right ";
    } else {
        cout << "acute ";
    }

    cout << "triangle\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}