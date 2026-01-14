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
boards

Confirmed Observations
If we have an all one row and column, then this board is connected. This is scene for boards that are all 1's


Guesses
As
10 and 01
01     10 
Seems like if we have a single one on both row and col, this should imply that it is disconnected. 

try to look for some feature that is observable in disconnected components. 

#######
......#
#######
.#.....
#######
.......
#######

##..
##..
..##
..##

if a row or column is empty, => it is connected. 

#.
..

.#
..

..
#.

..
.#

##
..

..
##

#.
#.

.#
.#

##
#.

##
.#

.#
##

#.
##

##
##

#.
.#

.#
#.

what is a strategy to handle the 2x2 grids?

###
#..
#.#

###
###
###


*/

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve_first() {
    int n, c; cin >> n >> c;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> rc(n), cc(n);
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++) cnt += a[i][j] == '1';
        rc[i] = cnt;
    }

    for(int j = 0; j < n; j++) {
        int cnt = 0;
        for(int i = 0; i < n; i++) cnt += a[i][j] == '1';
        cc[j] = cnt;
    }

    int ri, ci;
    if(c == 0) {
        if(*min_element(rc.begin(), rc.end()) < *max_element(cc.begin(), cc.end())) {
            ri = 0, ci = 0;
            for(int i = 1; i < n; i++) {
                if(rc[i] < rc[ri]) ri = i;
                if(cc[i] > cc[ci]) ci = i;
            }
        } else {
            ri = -1, ci = -1;
            for(int i = 0; i < n; i++) {
                if(a[i][0] == '0') ri = i;
                if(a[0][i] == '0') ci = i;
            }
            assert(ri != -1 && ci != -1);
        }
    } else {
        if(*max_element(rc.begin(), rc.end()) > *min_element(cc.begin(), cc.end())) {
            ri = 0, ci = 0;
            for(int i = 1; i < n; i++) {
                if(rc[i] > rc[ri]) ri = i;
                if(cc[i] < cc[ci]) ci = i;
            }
        } else {
            ri = -1, ci = -1;
            for(int i = 0; i < n; i++) {
                if(a[i][0] == '1') ri = i;
                if(a[0][i] == '1') ci = i;
            }
            assert(ri != -1 && ci != -1);
        }
    }

    cout << ri + 1 << " " << ci + 1 << '\n';

}

void solve_second() {
    int n; cin >> n;
    string r, c; cin >> r >> c;
    int cr = count(r.begin(), r.end(), '1');
    int cc = count(c.begin(), c.end(), '1');
    if(cr > cc) {
        cout << "1\n";
    } else if(cr < cc) {
        cout << "0\n";
    } else {
        cout << r[0] << '\n';
    }
}

int isconnected(int n, vector<vector<bool>> a) {
    int sx = -1, sy = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j]) {
                sx = i;
                sy = j;
            }
        }
    }
    vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};
    queue<array<int,2>> q;
    auto add_q = [&](int i, int j) {
        if(a[i][j]) {
            a[i][j] = 0;
            q.push({i, j});
        }
    };
    add_q(sx, sy);
    while(q.size()) {
        auto [x, y] = q.front();
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                add_q(nx, ny);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j]) return 0;
        }
    }
    return 1;
}

int check(int n, vector<vector<bool>> a, int row, int col) {
    for(int i = 0; i < n; i++) { //row i
        for(int j = 0; j < n; j++) { //col j
            int ok = 1;
            for(int k = 0; k < n; k++) {    
                if(((row >> k) & 1) != a[i][k]) ok = 0;
                if(((col >> k) & 1) != a[k][j]) ok = 0;
            }
            if(ok) return 1;
        }
    }
}

void find_partition(int n) {
    vector<array<int,2>> a;
    for(int i = 0; i < 1 << (n * 2); i++) {
        a.push_back({i & ((1 << n) - 1), i >> n});
    }
    for(int bm = 0; bm < 1 << (n * 2); bm++) {
        int ok = 1;
        for(int bd = 1; bd < 1 << (n * n); bd++) { //no empty boards. 
            vector<vector<bool>> board(n, vector<bool>(n));
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if((bd >> (i * j + j)) & 1) board[i][j] = 1;
                }
            }
            int f = 0;
            int connectivity = isconnected(n, board);
            for(int i = 0; i < 1 << (n * 2); i++) {

            }
        }

    }
}

void pb(int n, int bm) {
    vector<vector<bool>> board(n, vector<bool>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if((bm >> (i * j + j)) & 1) board[i][j] = 1;
            cout << board[i][j];
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int n, c; cin >> n >> c;
    // for(int i = 0; i < c; i++) {
    //     pb(n, rng() % (1 << (n * n)));
    //     cout << '\n';
    // }

    string type; cin >> type;
    int casi; cin >> casi;
    while(casi-->0) {
        if(type == "first") solve_first();
        if(type == "second") solve_second();
    }

    return 0;
}