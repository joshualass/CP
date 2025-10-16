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

/*
Incremental Induction

I store a current score current_score which stores the current number of people on the 
right that are losing to the number of people on the left. 

Cost[i] => How much will current_score change when I move element i over to the right?

Let's say I move a different person, j from the left to the right next. 

What happens to Cost[i]? 
If i beats j, then Cost[i] decreases because we moved j over and added 1 to our 
current_score but by adding i now, our score will decrease by 1, so Cost[i] decreases 
by 1. 

when we move j over, we added 1 to our current score because i on the left beats j on 
the right. so when we 

If j beats i, then what happens to Cost[i]? Well, element i is no longer losing to j
anymore, so we can also decrease Cost[i] by 1. 

###
Any either case, Cost[i] decreases by 1. 
###

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> c(n);
    for(int i = 1; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < i; j++) {
            if(s[j] == '0') {
                c[i]++;
            } else {
                c[j]++;
            }
        }
    }

    int cur = 0, res = 0;
    sort(c.begin(), c.end());
    for(int i = 0; i < n; i++) {
        cur += c[i] - i;
        res = max(res, cur);
    }

    cout << res << '\n';

    return 0;
}
