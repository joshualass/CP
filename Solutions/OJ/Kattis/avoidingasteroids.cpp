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

typedef long double ld;
using namespace std;

const ld epsilon = 1e-8;

struct vec3 {
    ld x, y, z;
};

struct vec2 {
    ld x, y;
};

void print_vec3(vec3 a) {
    cout << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}

vec2 add(vec2 a, vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

vec2 sub(vec2 a, vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

vec2 mul(vec2 a, ld s) {
    return {a.x * s, a.y * s};
}

vec2 div(vec2 a, ld s) {
    return {a.x / s, a.y / s};
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

vec3 cross(vec3 a, vec3 b) {
    ld x = a.y * b.z - a.z * b.y;
    ld y = -a.x * b.z + a.z * b.x;
    ld z = a.x * b.y - a.y * b.x;
    return {x, y, z};
}

ld dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

ld dist_sq(vec3 a, vec3 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

ld dist(vec3 a, vec3 b) {
    return sqrt(dist_sq(a, b));
}

ld len_sq(vec3 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

ld len(vec3 a) {
    return sqrt(len_sq(a));
}

vec3 add(vec3 a, vec3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 sub(vec3 a, vec3 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 mul(vec3 a, ld s) {
    return {a.x * s, a.y * s, a.z * s};
}

vec3 div(vec3 a, ld s) {
    return {a.x / s, a.y / s, a.z / s};
}

vec3 normalize(vec3 a) {
    return div(a, len(a));
}

vec3 in_vec3() {
    vec3 a;
    cin >> a.x >> a.y >> a.z;
    return a;
}

//return point on line p1 that is closest to p2
vec3 line_pt(vec3 p1, vec3 d1, vec3 p2) {
    vec3 dir = sub(p2, p1);
    return add(p1, mul(d1, dot(dir, d1)));
}

//return point on ray p1 that is closest to p2
vec3 ray_pt(vec3 p1, vec3 d1, vec3 p2) {
    vec3 pt = line_pt(p1, d1, p2);
    //clamp pt to ray
    ld d = dot(d1, sub(pt, p1));
    // cout << "DOT : " << d << " ";
    // print_vec3(pt);
    // print_vec3(p1);
    // print_vec3(d1);
    // cout << "\n";
    if(d < 0) return p1;
    return pt;
}

//returns distance from closest point on p1 to p2
ld line_pt_dist(vec3 p1, vec3 d1, vec3 p2) {
    vec3 pt = line_pt(p1, d1, p2);
    return dist(p2, pt);
}

ld ray_pt_dist(vec3 p1, vec3 d1, vec3 p2) {
    vec3 pt = ray_pt(p1, d1, p2);
    // cout << "RAY PT DIST : ";
    // print_vec3(p1);
    // print_vec3(d1);
    // print_vec3(p2);
    // print_vec3(pt);
    // cout << "\n";
    return dist(p2, pt);
}

ld segment_ray_dist(vec3 s1, vec3 e1, vec3 p2, vec3 d2) {
    ld low = 0, high = 1;
    ld ans = 1e18;
    while(high - low > epsilon) {
        // cout << "LH : " << low << " " << high << endl;
        ld m1 = low + (high - low) / 3.0 * 1.0;
        ld m2 = low + (high - low) / 3.0 * 2.0;
        vec3 pt1 = add(s1, mul(sub(e1, s1), m1));
        vec3 pt2 = add(s1, mul(sub(e1, s1), m2));
        ld v1 = ray_pt_dist(p2, d2, pt1);
        ld v2 = ray_pt_dist(p2, d2, pt2);
        ans = min(ans, min(v1, v2));
        if(v1 < v2) high = m2;
        else low = m1;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vec3 s, b;
    cin >> s.x >> s.y >> s.z >> b.x >> b.y >> b.z;
    int n;
    cin >> n;
    bool is_valid = true;
    for(int i = 0; i < n; i++) {
        vec3 p = in_vec3();
        vec3 d = in_vec3();
        int m;
        cin >> m;
        ld r = 0;
        for(int j = 0; j < m; j++) {
            vec3 pt = in_vec3();
            // cout << "DIST : " << dist(pt, p) << "\n";
            r = max(r, dist(pt, p));
        }
        //see if line segment s->b intersects with the infinite capsule 
        //starting at p in direction d with radius r
        d = normalize(d);
        ld dist = segment_ray_dist(s, b, p, d);
        if(dist < r) {
            is_valid = false;
        }
        // cout << "DIST : " << dist << " " << r << endl;
    }
    cout << (is_valid? "Go" : "Surrender") << "\n";

    return 0;
}
