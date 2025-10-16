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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n - 1);
    vector<vector<int>> mat(n, vector<int>(n));
    vector<int> ec(n);

    int bad = 0, same = 0;
    auto toggle = [&](int i, int j) -> void {
        // cout << "toggle i : " << i << " j : " << j << '\n';
        if(i == j) {
            same -= mat[i][j];
        } else {
            bad -= mat[i][j] != mat[j][i];
        }
        if(i != j) {
            if(mat[i][j]) {
                ec[i]--;
                ec[j]--;
            } else {
                ec[i]++;
                ec[j]++;
            }
        }
        mat[i][j] ^= 1;
        if(i == j) {
            same += mat[i][j];
        } else {
            bad += mat[i][j] != mat[j][i];
        }
    };

    for(int i = 0; i < n - 1; i++) {
        int m; cin >> m;
        for(int j = 0; j < m; j++) {
            int x; cin >> x;
            x--;
            adj[i].push_back(x);
            toggle(i + 1, x);
        }
    }

    auto check = [&](int i) -> bool {
        return bad - ec[i] == 0 && same == 0;
    };

    int res = INT_MAX;


    if(check(0)) {
        res = 0;
    }

    // cout << "init bad : " << bad  << "\n";
    // cout << "init ec : " << ec << '\n';

    for(int i = 0; i < n - 1; i++) {
        //undo the previous stuffs
        for(int to : adj[i]) toggle(i + 1, to);
        //add the next stuffs
        for(int to : adj[i]) toggle(i, to);
        if(check(i + 1)) {
            res = min(res, i + 1);
        }
        // cout << "i : " << i << " next bad : " << bad << '\n';
        // cout << "i : " << i << " ec : " << ec << '\n';
    }

    assert(res != INT_MAX);

    vector<int> in;
    for(int i = 0; i < n - 1; i++) {
        int idx = i + ((int) i >= res);
        for(int to : adj[i]) {
            if(to == res) in.push_back(idx);
        }
    }

    cout << res + 1;
    for(int x : in) cout << " " << x + 1;
    cout << '\n';

    return 0;
}
