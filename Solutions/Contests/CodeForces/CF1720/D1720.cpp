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
const int MAXN = 300000 * 30;

int p = 0;
int trie[MAXN][2]; //trie nodes
int mxs[MAXN][2][2]; // next maxes

int insert(int a, int b) { //a and b are the next things. 
    int cur = 0;
    int res = 0;
    for(int bit = 29; bit >= 0; bit--) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                int lhs = i ^ ((b >> bit) & 1);
                int rhs = j ^ ((a >> bit) & 1);
                if(lhs < rhs) {
                    res = max(res, mxs[cur][i][j]);
                }
            }
        }
        int nx = ((a >> bit) & 1) ^ ((b >> bit) & 1);
        if(trie[cur][nx] == 0) {
            trie[cur][nx] = ++p;
        }
        cur = trie[cur][nx];
    }

    res++;
    cur = 0;
    for(int bit = 29; bit >= 0; bit--) {
        int i = ((a >> bit) & 1), j = ((b >> bit) & 1);
        mxs[cur][i][j] = max(mxs[cur][i][j], res);
        int nx = ((a >> bit) & 1) ^ ((b >> bit) & 1);
        cur = trie[cur][nx];
    }
    return res;
}

void reset() {
    for(int i = 0; i <= p; i++) {
        for(int j = 0; j < 2; j++) {
            trie[i][j] = 0;
            for(int k = 0; k < 2; k++) {
                mxs[i][j][k] = 0;
            }
        }
    }
    p = 0;
}

void solve() {
    reset();
    int n; cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        int x = insert(a, i);
        // cout << "i : " << i << " x : " << x << '\n';
        res = max(res, x);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}