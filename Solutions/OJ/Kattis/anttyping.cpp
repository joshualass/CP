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
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int n = s.size();
    vvi c(9, vi(9, 0));
    for(int i = 1; i < n; i++) {
        int u = s[i - 1] - '1';
        int v = s[i] - '1';
        c[u][v] ++;
        c[v][u] ++;
    }
    vi p(9);
    for(int i = 0; i < 9; i++) p[i] = i;
    int ans = 1e9;
    do {
        int cans = 0;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                cans += abs(p[i] - p[j]) * c[i][j];
            }
        }
        assert((cans % 2) == 0);
        cans /= 2;
        cans += n;
        cans += p[s[0] - '1'];
        // if(cans < ans) {
        //     cout << "CANS : " << cans << " ";
        //     for(int i = 0; i < 9; i++) cout << p[i] << " ";
        //     cout << "\n";
        // }
        ans = min(ans, cans);
    }  while(next_permutation(p.begin(), p.end()));
    cout << ans << "\n";

}
