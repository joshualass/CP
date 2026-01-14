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

void solve() {
    
    int n; cin >> n;

    auto ask = [&](int i, int j) -> int {
        cout << "? " << i + 1 << " " << j + 1 << endl;
        int res; cin >> res;
        return res;
    };

    //first find penguin that is furthest from penguin 0 and is thus in a corner. 
    int fp = 0, fd = 0;
    for(int i = 1; i < n * n; i++) {
        int dist = ask(0, i);
        if(dist > fd) {
            fp = i;
            fd = dist;
        }
    }

    //fix fp to be one of the corners now. 

    //query distance from fp to all other penguins
    vector<int> fpds(n * n);

    for(int i = 0; i < n * n; i++) fpds[i] = ask(fp, i);

    int piv = -1;
    for(int i = 0; i < n * n; i++) {
        if(fpds[i] == n - 1) piv = i;
    }

    int fp2 = piv, fd2 = 0;
    for(int i = 0; i < n * n; i++) {
        if(fpds[i] == n - 1) {
            int dist = ask(piv, i);
            if(dist > fd2) {
                fp2 = i;
                fd2 = dist;
            }
        }
    }

    //now have 2 corners and query all distances from fp2
    vector<int> fpds2(n * n);
    for(int i = 0; i < n * n; i++) fpds2[i] = ask(fp2, i);

    vector<vector<int>> res(n, vector<int>(n));

    //reverse engineer each of the coordinates
    //assume fp is at upperleft, fp2 is at lowerleft
    for(int i = 0; i < n * n; i++) {
        int delta = fpds[i] - fpds2[i];
        int row = (delta + n - 1) / 2;
        int col = fpds[i] - row;
        res[row][col] = i;
    }

    cout << "!" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cout << res[i][j] + 1 << " ";
        cout << endl;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}