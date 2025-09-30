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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    
    array<int,3> nt = {-1,-1,-1};

    //queries [l, r] and returns how many 1's there are + handling nt. 
    auto ask = [&](int l, int r) -> int {
        int ql, qr;
        int sub = 0;
        if(nt[0] == -1) {
            if(nt[1] == l) {
                ql = nt[0], qr = r;
            } else if(nt[0] == r) {
                ql = l, qr = nt[1];
            } else {
                assert(0);
            }
            sub = (r - l) - nt[2];
        } else {
            ql = l, qr = r;
        }
        nt = {-1,-1,-1};
        cout << "? " << ql + 1 << " " << qr << endl;
        int res; cin >> res;
        return res - sub;
    };

    //we maintain that after our operations, the current array is the original array and we are able to discern where the 1 is. 
    int l = 0, r = n - 1;
    while(l != r) {

        int m = (l + r) / 2;
        int less = 

    }

    return 0;
}
