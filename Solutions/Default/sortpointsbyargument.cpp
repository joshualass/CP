// https://judge.yosupo.jp/problem/sort_points_by_argument
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<class F>
struct Point {
    F x, y;
    Point(): x(0), y(0) {}
    Point(const F& x, const F& y): x(x), y(y) {}

    void swap(Point& other) {
        using std::swap;
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

template <class F> void swap(const Point<F>& lhs, const Point<F>& rhs) {
    lhs.swap(rhs);
}

template <class F> inline auto operator -(const Point<F>& point) {
    return makePoint(-point.x, -point.y);
}

template <class F1, class F2> inline auto operator +(const Point<F1>& lhs, const Point<F2>& rhs) {
    return makePoint(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <class F1, class F2> inline auto operator -(const Point<F1>& lhs, const Point<F2>& rhs) {
    return makePoint(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <class F1, class F2> inline auto operator *(const F1& factor, const Point<F2>& rhs) {
    return makePoint(factor * rhs.x, factor * rhs.y);
}

template <class F1, class F2> inline auto operator *(const Point<F1>& lhs, const F2& factor) {
    return makePoint(factor * lhs.x, factor * lhs.y);
}

template <class F1, class F2> inline auto operator /(const Point<F1>& lhs, const F2& factor) {
    return makePoint(lhs.x / factor, lhs.y / factor);
}

//dot product
template <class F1, class F2> inline auto operator *(const Point<F1>& lhs, const Point<F2>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

//determinant / cross product 
template <class F1, class F2> inline auto operator ^(const Point<F1>& lhs, const Point<F2>& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}


//ccw functions which I don't know what they do
template <class F1, class F2> inline auto ccw(const Point<F1>& lhs, const Point<F2>& rhs) {
    return rhs ^ lhs;
}

template <class F1, class F2, class F3> inline auto ccw(const Point<F1>& lhs, const Point<F2>& rhs, const Point<F3>& origin) {
    return ccw(lhs - origin, rhs - origin);
}

//comparison operators
template <class F1, class F2> inline bool operator ==(const Point<F1>& lhs,const Point<F2>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
    /*with error
    ld epsilon = 1E-10;
    return (abs(lhs.x - rhs.x) < epsilon && abs(lhs.y - rhs.y) < episilon);
    */
}

// #define FUNC2(name, arg1, arg2, expr) \
// template <class F1, class F2> \
// inline auto name(const arg1, const arg2) -> decltype(expr) { return expr; }

// FUNC2(operator ==, Point<F1>& lhs, Point<F2>& rhs, lhs.x == rhs.x && lhs.y == rhs.y)

// #undef FUNC2

template <class F1, class F2> inline bool operator !=(const Point<F1>& lhs, const Point<F2>& rhs) {
    return !(lhs == rhs);
}

template <class F1, class F2> inline bool operator <(const Point<F1>& lhs, const Point<F2>& rhs) {
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

template <class F1, class F2> inline bool operator >(const Point<F1>& lhs, const Point<F2>& rhs) {
    return rhs < lhs;
}

template <class F1, class F2> inline bool operator <=(const Point<F1>& lhs, const Point<F2>& rhs) {
    return !(lhs > rhs);
}

template <class F1, class F2> inline bool operator >=(const Point<F1>& lhs, const Point<F2>& rhs) {
    return !(lhs < rhs);
}

//angles and rotations (counter-clockwise)
template <class F> inline auto angle(const Point<F>& point) {
    return atan2(point.y, point.x);
}

template <class F1, class F2> inline auto angle(const Point<F1>& lhs, const Point<F2>& rhs) {
    return atan2(lhs ^ rhs, lhs * rhs);
}

template <class F1, class F2, class F3> inline auto angle(const Point<F1>& lhs, const Point<F2>& rhs, const Point<F3>& origin) {
    return angle(lhs - origin, rhs - origin);
}

template <class F1, class F2, class F3> inline auto rotate(const Point<F1>& point, const Point<F2>& angleSin, const Point<F3>& angleCos) {
    return makePoint(angleCos * point.x - angleSin * point.y,
                     angleSin * point.x + angleCos * point.y
    );
}

template <class F1, class F2> inline auto rotate(const Point<F1>& point, const F2& angle) {
    return rotate(point, sin(angle), cos(angle));
}

template <class F1, class F2, class F3> inline auto rotate(const Point<F1>& point, F2& angle, const Point<F3>& origin) {
    return origin + rotate(point - origin, angle);
}

template <class F> inline auto perp(const Point<F>& point) {
    return makePoint(-point.y, point.x);
}

// distances
template <class F> inline auto abs(const Point<F>& point) {
    return point * point;
}

//normal distance
template <class F> inline auto norm(const Point<F>& point) {
    return sqrt(abs(point));
}

//normal distance
template <class F1, class F2> inline auto dist(const Point<F1>& lhs, const Point<F2>& rhs) {
    return norm(lhs - rhs);
}

template <class F1, class F2> inline auto dist2(const Point<F1>& lhs, const Point<F2>& rhs) {
    return abs(lhs - rhs);
}

template <class F1, class F2> inline auto bisector(const Point<F1>& lhs, const Point<F2>& rhs) {
    return lhs * norm(rhs) + rhs * norm(lhs);
}

template<class F>
struct AngleCompare {

    const Point<F> origin;
    const bool zero;

    AngleCompare(const Point<F>& origin = Point<F>()): origin(origin), zero(origin == Point<F>()) { }

    template <class F1, class F2>
    bool operator () (const Point<F1>& lhs, const Point<F2>& rhs) const {
        return zero ? ccw(lhs, rhs) < 0 : ccw(lhs, rhs, origin) < 0;
    }

};

template <class Iterator, class F>
void sortByAngle(Iterator first, Iterator last, const Point<F>& origin) {
    first = partition(first, last, [&origin](const decltype(*first)& point) {
        return point == origin;
    });

    auto pivot = partition(first, last, [&origin](const decltype(*first)& point) {
        return point > origin;
    });

    AngleCompare<F> acmp(origin);
    sort(first, pivot, acmp);
    sort(pivot, last, acmp);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<Point<ld>> v(n);
    for(auto &x: v) cin >> x;
    
    // sortByAngle(v.begin(), v.end(), makePoint((ld) 0,(ld)0));

    sort(v.begin(), v.end(), [](Point<ld> &lhs, Point<ld>& rhs) {
        return angle(lhs) < angle(rhs);
    });
    cout << fixed << setprecision(0);
    for(auto x : v) cout << x << '\n';



    return 0;
}