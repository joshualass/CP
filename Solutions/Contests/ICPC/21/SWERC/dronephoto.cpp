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
2021-2022 ICPC Southwestern European Regional Contest (SWERC 2021-2022)
Drone Photo

Spent a while thinking about this problem and how it could be possible. 
i originally tried some approaches of iterating over rows and columns of pairs of elements in the same row, but all approaches of this type tle. 

i looked at the problem tags and saw math and sortings, leading to think of a PIE type of approach. 

With PIE in mind, I was able to develop the following
We iterate over the points in increasing order, and count the number of pairs of points where two corners have been visited, but the other two have not (violation). 

To count this, we iterate over all the points and count the number of visited points that do not share the same row or column. 
We can observe that for each pair of points that do not share a row or column, they will be counted exactly once, regardless of our order, so we can set 
part1 = n * n * (n - 1) * (n - 1) / 2. 

Next, with PIE, this will overcount some things. In particular, we overcount when there is a point that does not share a row and column, but there already exists a point
that shares a row and column with both points. 
There are two cases that can happen for this in the rows and columns. We look at the order of the two points. If we place a point that shares a column with the 
row, then we know we should uncount equal to the count of the number of unvisited cells in the column. 
For the case where the next cell we visit is next to the first cell, we can observe this case happens exactly empty cols * empty rows times. 

Lastly, we overremove the cases where we place a point and we doubly remove the point that does not share a row or column as there are two points that are already placed
and that share a row / column with both points. There are a total of n * n * (n - 1) * (n - 1) / 4 points to recount. 

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,3>> a;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            a.push_back({x, i, j});
        }
    }

    sort(a.begin(), a.end());
    ll part1 = 1LL * n * n * (n - 1) * (n - 1) / 2;
    ll part2 = 0;
    
    vector<int> rvis(n), cvis(n);
    for(auto [_, r, c] : a) {
        rvis[r]++;
        cvis[c]++;

        int er = n - rvis[r], ec = n - cvis[c];
        part2 += 1LL * er * ec;

        part2 += 1LL * (rvis[r] - 1) * ec;
        part2 += 1LL * (cvis[c] - 1) * er;

    }

    ll part3 = 1LL * n * n * (n - 1) * (n - 1) / 4;

    // cout << "part1 : " << part1 << '\n';
    // cout << "part2 : " << part2 << '\n';
    // cout << "part3 : " << part3 << '\n';

    cout << 1LL * n * n * (n - 1) * (n - 1) / 4 - (part1 - part2 + part3) << '\n';

    return 0;
}
