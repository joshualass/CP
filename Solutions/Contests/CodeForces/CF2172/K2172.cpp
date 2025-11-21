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
const int MAXN = 1e6;
int cnts[MAXN + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q; cin >> n >> m >> q;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    auto work = [&](int i, int j, int dx, int dy, int stop, int delta) -> void {
        // cout << "work : " << s << endl;
        ll sum = 0;
        ll last_num = 0;
        ll last_prod = 1;
        char p = '+';
        // vector<pair<vector<ll>, ll>> sums;
        // sums.push_back({{0}, 1});

        for(int k = 0; k < stop; k++) {
            char c = a[i + dx * k][j + dy * k];
            if((p == '*' || p == '+') && (c == '*' || c == '+')) break;
            if(c == '+') {
                sum += last_prod;
                last_num = 0;
                last_prod = 1;
                // sum += sums.back().second;
                // sums.push_back({{0}, 1});
                if(sum > MAXN) break;
            } else if(c == '*') {
                // sums.back().first.push_back(0);
                last_num = 0;
            } else {
                // cout << "c : " << c << endl;
                if(last_num == 0) {
                    // cout << "s0" << endl;
                    // sums.back().first.back() = stoi(string(1, c));
                    // cout << "s0 done" << endl;
                    last_num = c - '0';
                } else {
                    // cout << "s1" << endl;
                    // sums.back().second /= sums.back().first.back();
                    last_prod /= last_num;
                    // cout << "prev back : " << sums.back().first.back() << endl;
                    // sums.back().first.back() = stoi(to_string(sums.back().first.back()) + string(1, c));
                    last_num = last_num * 10 + (c - '0');
                    // cout << "s1" << endl;
                }
                last_prod *= last_num;
                // sums.back().second *= sums.back().first.back();
                if(last_prod> MAXN) break;
                ll add = sum + last_prod;
                if(add > MAXN) break;
                // if(add == 3) {
                //     cout << "adding to 3 string : " << s << '\n';
                // }
                cnts[add] += delta;
            }
            p = c;
        }
    };

    // auto _work = [&](string s) -> void {
    //     for(int i = 0; i < s.size(); i++) work(s.substr(i));
    //     reverse(s.begin(), s.end());
    //     for(int i = 0; i < s.size(); i++) work(s.substr(i));
    // };

    vector<int> dx = {1,1,1,0,-1,-1,-1,0}, dy = {1,0,-1,-1,-1,0,1,1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < 8; k++) {
                int stop = 0;
                for(int l = 0; i + dx[k] * l >= 0 && i + dx[k] * l < n && j + dy[k] * l >= 0 && j + dy[k] * l < m; l++) {
                    // s.push_back(a[i + dx[k] * l][j + dy[k] * l]);
                    stop++;
                }
                // if(l == 0 && k == 0 || l) work(s);
                work(i, j, dx[k], dy[k], stop, 1);
            }
            // work(string(1, a[i][j]), -7);
            work(i, j, 0, 0, 1, -7);
        }
    }

    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        cout << cnts[x] << '\n';
    }

    return 0;
}
