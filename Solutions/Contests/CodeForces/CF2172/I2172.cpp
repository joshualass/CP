#pragma GCC optimize ("Ofast")

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstring>
typedef long long ll;
typedef double ld;
using namespace std;
typedef vector<int> vi;

const ld PI = acos(-1);

template<typename T>
struct vec2 {
    T x, y;
    bool operator<(vec2 other) const { return tie(x, y) < tie(other.x, other.y); }
    bool operator==(vec2 other) const { return tie(x, y) == tie(other.x, other.y); }
    vec2 operator+(vec2 other) const { return {x + other.x, y + other.y}; }
    vec2 operator-(vec2 other) const { return {x - other.x, y - other.y}; }
    vec2 operator*(T s) const { return {x * s, y * s}; }
    vec2 operator/(T s) const { return {x / s, y / s}; }
    T dot(vec2 other) const {return x * other.x + y * other.y; }
    T cross(vec2 other) const { return x * other.y - y * other.x; }
    T cross(vec2 a, vec2 b) const { return (a-*this).cross(b-*this); }
    T dist2() const {return x * x + y * y;}
    T dist() const {return sqrt(this->dist2());}
};

ld cap_area(ld r, ld x) {
    ld theta = acos(x / r) * 2.0;
    ld y = sin(theta / 2.0) * r;
    return theta / 2.0 * r * r - x * y;
}

vector<vec2<ll>> convex_hull(vector<vec2<ll>> pts) {
    if(pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<vec2<ll>> h(pts.size() + 1);
    int s = 0, t = 0;
    for(int it = 2; it --; s = --t, reverse(pts.begin(), pts.end())) {
        for(vec2 p : pts) {
            while(t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t --;
            h[t ++] = p;
        }
    }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int sgn(ld x) {
    if(x == 0) return 0;
    if(x < 0) return -1;
    else return 1;
}

int sideof(vec2<ld> s, vec2<ld> e, vec2<ld> p) {
    return sgn(s.cross(e, p));
}

ld pt_line_proj_dist(vec2<ld> pt, vec2<ld> l1, vec2<ld> l2) {
    vec2 to_line = l1 - pt;
    vec2 tang = (l2 - l1);
    tang = (tang / tang.dist());
    tang = tang * tang.dot(to_line);
    to_line = to_line - tang;
    return to_line.dist();
}

const vec2<ld> orig = {0, 0};
const int RANDMAX = (1 << 20);

ld randf() {
    return (ld) (rand() % RANDMAX) / (ld) RANDMAX;
}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    int n;
    ld r;
    cin >> n >> r;
    vector<vec2<ll>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    // shuffle(a.begin(), a.end(), rng);
    // srand(time(0));
    // for(int i = 0; i < n; i++) {
    //     // cout << "GEN : " << i << endl;
    //     while(true) {
    //         ld x = randf() * 2 * r - r;
    //         ld y = randf() * 2 * r - r;
    //         // cout << "X Y : " << x << " " << y << endl;
    //         if(sqrt(x * x + y * y) > 0.9 * r) continue;
    //         a[i] = {x, y};
    //         break;
    //     }
    // }
    // cout << "DONE GEN" << endl;
    a = convex_hull(a);
    n = a.size();
    // cout << "HULL : \n";
    // for(int i = 0; i < n; i++) cout << a[i].x << " " << a[i].y << "\n";
    vector<vec2<ld>> b(n);
    for(int i = 0; i < n; i++) b[i] = {(ld) a[i].x, (ld) a[i].y};
    // cout << "N : " << n << endl;
    if(n == 1) {
        ld ans = PI * r * r / 2.0;
        cout << fixed << setprecision(10) << ans << "\n";
        return 0;
    }
    ld mnx = r;
    for(int i = 0; i < n; i++) {
        vec2 u = b[i], v = b[(i + 1) % n];
        if(sideof(u, v, orig) <= 0) mnx = 0;
        else mnx = min(mnx, pt_line_proj_dist(orig, u, v));
        if(mnx == 0) break;
    }
    ld ans = cap_area(r, mnx);
    cout << fixed << setprecision(10) << ans << "\n";

    return 0;
}
