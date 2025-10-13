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
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    auto _solve_left_area = [&]() -> vector<ld> {
        vector<array<int,2>> hull;

        auto get_ray = [&](array<int,2> one, array<int,2> two) -> array<int,2> {
            return {two[0] - one[0], two[1] - one[1]};
        };

        //try to figure out which ray goes up more per unit x to the right. 
        //all rays have a positive x component. 
        //returns true if ray_2 is steeper / greater than ray_1
        auto compare_rays = [&](array<int,2> ray_1, array<int,2> ray_2) -> bool {
            ld up_1 = ((ld) ray_1[1]) / ray_1[0];
            ld up_2 = ((ld) ray_2[1]) / ray_2[0];

            return up_1 < up_2;
        };

        auto insert_hull = [&](array<int,2> pt) -> void {
            while(hull.size() >= 2) {
                array<int,2> prev_ray = get_ray(hull[hull.size() - 2], hull[hull.size() - 1]);
                array<int,2> next_ray = get_ray(hull[hull.size() - 2], pt);
                //if we have a steeper next ray, then we are good
                if(compare_rays(prev_ray, next_ray)) {
                    break;
                } else {
                    hull.pop_back();
                }
            }
            hull.push_back(pt);
        };

        //find the largest angle we can make
        auto query = [&](array<int,2> pt) -> array<int,2> {
            int l = 0, r = hull.size() - 1;
            while(l != r) {
                int m = (l + r) / 2;
                array<int,2> ray_prev = get_ray(hull[m], hull[m + 1]);
                array<int,2> ray_pt = get_ray(hull[m], pt);

                if(compare_rays(ray_prev, ray_pt)) {
                    l = m + 1;
                } else {
                    r = m;
                }
            }
            return get_ray(hull[l], pt);
        };

        vector<ld> res(n);
        for(int i = 0; i + 1 < n; i++) {
            if(i) {
                auto [dx, dy] = query(a[i]);
                ld height = a[i][1];
                ld width = dx * height / dy;
                res[i] = width;
            }
            insert_hull(a[i]);
        }
        return res;
    };

    vector<ld> l = _solve_left_area();
    int len = a[n - 1][0];

    auto rev_a = [&]() -> void {
        for(int i = 0; i < n; i++) {
            a[i][0] = len - a[i][0];
        }
        reverse(a.begin(), a.end());
    };

    rev_a();


    vector<ld> r = _solve_left_area();
    reverse(r.begin(), r.end());

    rev_a();

    // cout << "l : " << l << '\n';
    // cout << "r : " << r << '\n';

    ld res = 0;
    for(int i = 1; i + 1 < n; i++) {
        ld area_here = (l[i] + r[i]) * a[i][1];
        // cout << "i : " << i << " area_here : " << area_here << '\n';
        res = max(res, area_here);
    }
    cout << fixed << setprecision(10) << res / 2 << '\n';

    return 0;
}
