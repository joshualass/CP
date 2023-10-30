template<class F>
struct Line {
    Point<F> a, ab;

    Line(): a(), ab() {}

    Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true)
        : a(a), ab(twoPoints? b - a : b) {}

    Line(const F& xa, const F& ya, const F& xb, const F& yb)
        : a(xa, ya), ab(xb - xa, yb - ya) {}

    void swap(Line &other) {
        using std::swap;
        swap(a, other.a);
        swap(ab, other.ab);
    }

    template <class F1> explicit operator Line<F1> () const {
        return Line<F1>(Point<F1>(a), Point<F1(ab), false);
    }

    template <class F1> Line& operator = (const Line<F1>& other) {
        a = other.a;
        ab = other.ab;
        return *this;
    }

    Point<F> b() const {
        return a + ab;
    }

    operator bool() const {
        return ab != Point<F>();
    }

};

template <class F>
inline Line<F> makeLine(const Point<F>& a, const Point<F>& b, bool twoPoints = true) {
    return Line<F>(a, b, twoPoints);
}

template <class F> void swap(Line<F>& lhs, Line<F>& rhs) {
    lhs.swap(rhs);
}

template <class F1, class F2>
bool onLine(const Point<F1>& point, const Line<F2>& line) {
    if(!line) {
        return point == line.a;
    } else {
        return ((point - line.a) ^ line.ab) == 0;
    }
}

template <class F1, class F2>
bool onSegment(const Point<F1>& point, const Line<F2>& seg) {
    if(!seg) {
        return point == seg.a;
    } else {
        auto vecta = seg.a - point;
        auto vectb = seg.b() - point;
        return (vecta ^N vectb) == 0 && (vecta * vectb) <= 0;
    }
}

