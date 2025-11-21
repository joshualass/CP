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
ld eps = 1e-9;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << fixed << setprecision(10) << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto solve_perm = [&](auto self, vector<ld> a) -> bool {

        if(a.size() == 1) {
            return abs(a[0] - 3.4285714286) < eps;
        }

        for(int i = 0; i + 1 < a.size(); i++) {
            vector<ld> copy = a;
            ld l = copy[i], r = copy[i+1];
            copy.erase(copy.begin() + i);
            copy.erase(copy.begin() + i);

            for(int j = 0; j < 4; j++) {
                //do add
                ld lhs = l, rhs = r;
                if(j & 1) l *= -1;
                if(j & 2) r *= -1;
                {
                    auto c = copy;
                    c.insert(c.begin() + i, lhs + rhs);
                    if(self(self, c)) {
                        if(a.size() == 2) cout << "a : " << a << endl;
                        return 1;
                    }
                }
                {
                    auto c = copy;
                    c.insert(c.begin() + i, lhs - rhs);
                    if(self(self, c)) {
                        if(a.size() == 2) cout << "a : " << a << endl;    
                        return 1;
                    }
                }
                {
                    auto c = copy;
                    c.insert(c.begin() + i, lhs * rhs);
                    if(self(self, c)) {
                        if(a.size() == 2) cout << "a : " << a << endl;    
                        return 1;
                    }
                }
                {
                    auto c = copy;
                    c.insert(c.begin() + i, lhs / rhs);
                    if(self(self, c)) {
                        if(a.size() == 2) cout << "a : " << a << endl;    
                        return 1;
                    }
                }
            }
        }
        return 0;
    };

    vector<ld> perm = {4,4,7};
    while(1) {
        if(solve_perm(solve_perm, perm)) {
            cout << "perm : " << perm << endl;
        }
        if(!next_permutation(perm.begin(), perm.end())) break;
    }    

    return 0;
}
