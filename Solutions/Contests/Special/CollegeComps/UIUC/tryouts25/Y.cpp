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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<ld>> matmult(vector<vector<ld>> &a, vector<vector<ld>> &b) {
    int n = a.size();
    vector<vector<ld>> res(n,vector<ld>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int z = 0; z < n; z++) {
                res[i][j] += a[i][z] * b[z][j];
            }
        }
    }
    return res;
}
//use notation of [from][to]
vector<vector<ld>> matexp(vector<vector<ld>> mat, ll pow) {
    int n = mat.size();
    vector<vector<ld>> result(n,vector<ld>(n));
    result[0][0] = 1;
    while(pow) {
        if(pow & 1) {
            result = matmult(result,mat); //result is the current matrix, mat is the binexp matrix
        }
        mat = matmult(mat,mat);
        pow >>= 1;
    }
    return result;
}

const int len = 1000;
ld dp[len];

void solve(ll n) {
    // vector<vector<ld>> mat = {
    //     {0, .5}, 
    //     {1, .5}
    // };
    // auto res = matexp(mat, n - 1);
    // ld p = res[0][0] + res[1][0];

    if(n >= 1000) {
        cout << fixed << setprecision(10) << "33.3333333333 66.6666666667\n";
    } else {
        cout << fixed << setprecision(10) << dp[n - 1] * 100 << " " << (1 - dp[n - 1]) * 100 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp[0] = 1;
    for(int i = 2; i < len; i++) dp[i] = (dp[i-1] + dp[i-2]) / 2;

    // cout << "dp : " << dp << '\n';

    // for(int i = 1; i <= 20; i++) {
    //     solve(i);
    // }

    ll n; cin >> n;

    solve(n);

    return 0;
}
