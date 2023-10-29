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

template <class F1, class F2, class F3> inline auto angle(Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin) {
    return angle(lhs - origin, rhs - origin);
}

template <class F1, class F2, class F3> inline auto rotate(Point<F1>& point, Point<F2>& angleSin, Point<F3>& angleCos) {
    return makePoint(angleCos * point.x - angleSin * point.y,
                     angleSin * point.x + angleCos * point.y
    );
}

template <class F1, class F2> inline auto angle(Point<F1>& lhs, F2& angle) {
    return rotate(point, sin(angle), cos(angle));
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

