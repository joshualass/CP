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
current thoughts are some 4d segment tree data structure could work

fix a corner and then binary search the other corner. 

This would be O(n^2 (logn)^5)

Lots of these old ideas, spent a while on it

On the third week, derive the good idea in 15 minutes. 
The thought process to arrive at the idea is to analyze for each value, what upper left hand corner positions of squares of the same size contain all occurrences of this value?
The structure is a rectangle ...

With this, we iterate over each size, then see for each upper left corner, we can count how many numbers are all contained. Basically, we are able to brute force every square position and size 
with this approach. 

Binary Search bait ...

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<array<int,4>> a(n * n, {-1,-1,-1,-1}); //{row min, row max, col min, col max}

    int dist = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int x; cin >> x;
            x--;
            if(a[x][0] == -1) {
                a[x] = {i,i,j,j};
                dist++;
            } else {
                a[x][0] = min(a[x][0], i);
                a[x][1] = max(a[x][1], i);
                a[x][2] = min(a[x][2], j);
                a[x][3] = max(a[x][3], j);
            }
        }
    }

    if(dist <= k) {
        cout << k - dist << "\n";
        return 0;
    }

    int f = 0;

    for(int l = 0; l < n; l++) {
        vector<vector<int>> p(n - l, vector<int>(n - l));
        for(int i = 0; i < n * n; i++) {
            if(a[i][0] != -1) {
                int minr = max(0, a[i][1] - l);
                int maxr = min(n - l - 1, a[i][0]);
                int minc = max(0, a[i][3] - l);
                int maxc = min(n - l - 1, a[i][2]);

                if(minr <= maxr && minc <= maxc) {

                    p[maxr][maxc]++;
                    if(minr) {
                        p[minr - 1][maxc]--;
                    }
                    if(minc) {
                        p[maxr][minc - 1]--;
                    }
                    if(minr && minc) {
                        p[minr - 1][minc - 1]++;
                    }
                }                
            }
        }

        //prop down through r first. 
        for(int i = n - l - 1; i >= 0; i--) {
            for(int j = n - l - 1; j >= 0; j--) {
                if(i) p[i-1][j] += p[i][j];
            }
        }
        //prop left through c second
        for(int i = n - l - 1; i >= 0; i--) {
            for(int j = n - l - 1; j >= 0; j--) {
                if(j) p[i][j-1] += p[i][j];
            }
        }
        //now check
        for(int i = n - l - 1; i >= 0; i--) {
            for(int j = n - l - 1; j >= 0; j--) {
                int sum = p[i][j];
                if(dist - sum == k || dist - sum == k - 1) f = 1;
            }
        }
    }

    cout << (f ? 1 : 2) << '\n';

    return 0;
}
