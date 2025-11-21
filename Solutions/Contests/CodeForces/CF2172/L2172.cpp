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
const int inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;

    //given a binary vector, for each op count from 0 to a.size() + 1, return the most possible amount of 1's after doing ops[i] ops. 
    auto get_ops = [](vector<int> a, int mx) -> vector<int> {
        if(a.empty()) return {0};
        // cout << "a" << endl;
        // for(int x : a) cout << x << " ";
        // cout << endl;
        vector<array<int,2>> dp(a.size() + 1, array<int,2>{-inf, -inf}), nx(a.size() + 1, array<int,2>{-inf, -inf});
        //dp[i][j] => (given that we've done i ops, whether the current bit must be toggled) => score

        dp[0][0] = 0;

        for(int i = 0; i < a.size(); i++) {
            nx.assign(a.size() + 1, array<int,2>{-inf, -inf});
            for(int j = 0; j < dp.size(); j++) { //current number of operations
                for(int k = 0; k < 2; k++) { //previous k
                    for(int l = 0; l < 2; l++) { //whether we do an op or not. 
                        if(j + l < dp.size()) {
                            nx[j + l][l] = max(nx[j + l][l], dp[j][k] + (a[i] ^ k ^ l));
                        }
                    }
                }
            }
            swap(dp, nx);
        }

        vector<int> res(a.size() + 1);
        for(int i = 0; i <= a.size(); i++) {
            for(int j = 0; j < mx; j++) {
                res[i] = max(res[i], dp[i][j]);
            }
        }
        // cout << "no seg fault" << endl;
        return res;
    };

    string s; cin >> s;
    vector<int> res(m + 1);

    for(int i = 1; i <= k; i++) {
        vector<int> a;
        for(int j = i; j < n; j += k) {
            a.push_back(s[j] != s[j-1]);
        }

        // cout << "i : " << i << endl;

        // cout << "a" << endl;
        // for(int x : a) cout << x << " ";
        // cout << endl;
        vector<int> ops;
        if(i == k) {
            reverse(a.begin(), a.end());
            ops = get_ops(a, 2);
        } else if((n - i) % k == 0) {
            ops = get_ops(a, 2);
        } else {
            ops = get_ops(a, 1);
        }

        // cout << "ops" << endl;
        // for(int x : ops) cout << x << " ";
        // cout << endl;

        for(int j = m; j >= 0; j--) {
            for(int l = ops.size() - 1; l >= 0; l--) {
                if(j+l <= m) res[j+l] = max(res[j+l], res[j] + ops[l]);
            }
        }
    }

    cout << *max_element(res.begin(), res.end()) + 1 << '\n';

    return 0;
}
