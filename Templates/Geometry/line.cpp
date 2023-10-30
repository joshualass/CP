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

template<class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

template <class F1, class F2>
distF<F1, F2> distLine(const Point<F1>& point, const Line<F2>& line) {
    if (!line) {
        return dist(point, line.a);
    } else {
        return abs((point - line.a) ^ line.ab) / norm(line.ab);
    }
}

template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1>& point, const Line<F2>& seg) {
    if(((point - seg.a) * seg.ab) <= 0) {
        return dist(point, seg.a);
    } else if(((point - seg.b()) * seg.ab) >= 0) {
        return dist(point, seg.b());
    } else {
        return distLine(point,seg);
    }
}

template <class F1, class F2, class F3>
void projection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
  res = line.a;
  if (line) res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

template <class F1, class F2, class F3>
void reflection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
  projection(point, line, res);
  res = 2 * res - point;
}

template <class F1, class F2, class F3>
void closest(const Point<F1>& point, const Line<F2>& seg, Point<F3>& res) {
  if (((point - seg.a) * seg.ab) <= 0) res = seg.a;
  else if (((point - seg.b()) * seg.ab) >= 0) res = seg.b();
  else projection(point, seg, res);
}

template <int TYPE> struct EndpointChecker {};

template <> struct EndpointChecker<0> {  // no endpoint (ray)
  template <class F> bool operator ()(const F& a, const F& b) const { 
    return true; 
    }
};

template <> struct EndpointChecker<1> {  // closed endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { 
    return a <= b; 
    }
};

template <> struct EndpointChecker<2> {  // open endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { 
    return a < b; 
    }
};

template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersectLines(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {

  assert(lhs && rhs);
  auto s = lhs.ab ^ rhs.ab;

  if (s == 0) return false;

  auto ls = (rhs.a - lhs.a) ^ rhs.ab;
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;

  if (s < 0) s = -s, ls = -ls, rs = -rs;

  bool intersect =
    EndpointChecker<LA>()(decltype(ls)(0), ls) && EndpointChecker<LB>()(ls, s) &&
    EndpointChecker<RA>()(decltype(rs)(0), rs) && EndpointChecker<RB>()(rs, s);

  if (intersect) res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
  return intersect;
}

template <class F1, class F2, class F3>
bool intersectClosedSegments(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
  return intersectLines<1, 1, 1, 1>(lhs, rhs, res);
}

template <class F1, class F2, class F3>
bool intersectSegments(const Line<F1>& lhs, const Line<F2>& rhs, Line<F3>& res) {
  auto s = lhs.ab ^ rhs.ab;
  auto ls = (rhs.a - lhs.a) ^ rhs.ab;

  if (s == 0) {
    if (ls != 0) return false;

    auto lhsa = lhs.a, lhsb = lhs.b();
    auto rhsa = rhs.a, rhsb = rhs.b();

    if (lhsa > lhsb) swap(lhsa, lhsb);
    if (rhsa > rhsb) swap(rhsa, rhsb);

    res = Line<F3>(max(lhsa, rhsa), min(lhsb, rhsb));

    return res.ab >= Point<F3>();
  }
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;

  if (s < 0) s = -s, ls = -ls, rs = -rs;

  bool intersect = 0 <= ls && ls <= s && 0 <= rs && rs <= s;

  if (intersect)
    res = Line<F3>(lhs.a + lhs.ab * static_cast<F3>(ls) / s, Point<F3>());
    
  return intersect;
}