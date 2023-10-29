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