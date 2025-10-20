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
#include <utility>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;


void print_seg(pii x) {
    x.first ++;
    x.second ++;
    if(x.first == x.second) cout << x.first;
    else cout << x.first << "-" << x.second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c, n;
    cin >> c >> n;
    vector<bool> v(c);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x --;
        v[x] = true;
    }
    vector<pii> er, cr;
    for(int i = 0; i < c;) {
        int r = i;
        while(r != c && v[r] == v[i]) r ++;
        if(v[i]) er.push_back(pair<int, int>(i, r - 1));
        else cr.push_back(pair<int, int>(i, r - 1));
        i = r;
    }
    assert(er.size() != 0);
    assert(cr.size() != 0);
    cout << "Errors: "; 
    print_seg(er[0]);
    for(int i = 1; i < er.size(); i++) {
        if(i == er.size() - 1) {
            cout << " and ";
            print_seg(er[i]);
        }
        else {
            cout << ", ";
            print_seg(er[i]);
        }
    }
    cout << "\n";
    cout << "Correct: ";
    print_seg(cr[0]);
    for(int i = 1; i < cr.size(); i++) {
        if(i == cr.size() - 1) {
            cout << " and ";
            print_seg(cr[i]);
        }
        else {
            cout << ", ";
            print_seg(cr[i]);
        }
    }
    cout << "\n";

    return 0;
}
