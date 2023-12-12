#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<class F>
struct Point {
    F x, y;
    int id;
    Point(): x(0), y(0) {}
    Point(const F& x, const F& y, int id): x(x), y(y), id(id) {}

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
    return Point<F>(x, y, -1);
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
    cout << fixed << setprecision(5);
    int n;
    ld w, h; cin >> n >> w >> h;

    vector<Point<ld>> v;
    bool left = 1, right = 1, up = 1, down = 1;
    for(int i = 0; i < n; i++) {
        ld x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if(x1 != 0 && x2 != 0) {
            left = 0;
        }
        if(y1 != 0 && y2 != 0) {
            down = 0;
        }
        if(x1 != w && x2 != w) {
            right = 0;
        }
        if(y1 != h && y2 != h) {
            up = 0;
        }
        v.push_back(Point(x1,y1,i));
        v.push_back(Point(x2,y2,i));
    }
    
    if(left) {
        cout << "1\n0.01 0 0.01 " << h << '\n';
        return 0;
    }
    if(down) {
        cout << "1\n0 0.01 " << w << " 0.01\n";
        return 0;
    }
    if(right) {
        cout << "1\n" << w - 0.01 << " 0 "<< w - 0.01 << " " << h << '\n';
        return 0;        
    }
    if(up) {
        cout << "1\n0 " << h - 0.01 << " " << w << " " << h - 0.01 << "\n";
        return 0;    
    }

    sortByAngle(v.begin(), v.end(), Point(w/2,h/2,-1));

    // for(auto x : v) cout << x << '\n';
    // for(int i = 0; i < v.size(); i++) {
    //     cout << "i : " << i << " --- " << v[i] << '\n';
    // }

    int s = 0, t = 0;

    vector<bool> inside(n);
    int cnt = 0;
    pair<int,int> ans = {-1,-1};
    while(s != n * 2) {
        while(inside[v[t % (n * 2)].id] == 0) {
            inside[v[t++ % (n * 2)].id] = 1;
            cnt++;
        }
        if(cnt == n) {
            // cout << "upd ans : " << s << " " << t << '\n';
            ans = {s % (n * 2), t % (n * 2)};
        }
        inside[v[s++].id] = 0; cnt--;
    }

    if(ans.first != -1 || ans.second != -1) {
        cout << "1\n";
        Point first = v[ans.first];
        Point second = v[ans.second];
        // cout << "first : " << first << " second : " << second << '\n';
        if(first.x == w) {
            cout << first.x << " " << first.y - 0.01 << ' ';
        } else if(first.y == h) {
            cout << first.x + 0.01 << " " << first.y << ' ';
        } else if(first.x == 0) {
            cout << first.x << " " << first.y + 0.01 << ' ';
        } else if(first.y == 0) {
            cout << first.x - 0.01 << " " << first.y << ' ';
        }
        if(second.x == w) {
            cout << second.x << " " << second.y - 0.01 << '\n';
        } else if(second.y == h) {
            cout << second.x + 0.01 << " " << second.y << '\n';
        } else if(second.x == 0) {
            cout << second.x << " " << second.y + 0.01 << '\n';
        } else if(second.y == 0) {
            cout << second.x - 0.01 << " " << second.y << '\n';
        }        
    } else {
        cout << "2\n";
        cout << "0 0.01 " << w << " " << h - 0.01 << '\n';
        cout << w << " 0.01 0.01 " << h << '\n';
    }


    return 0;
}