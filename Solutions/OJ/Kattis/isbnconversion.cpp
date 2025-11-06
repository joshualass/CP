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
    
    string s; cin >> s;
    int ok = 1;

    //check hyphens at the front / back
    if(s.front() == '-' || s.back() == '-') {
        ok = 0;
    }

    //check double hyphen
    if(s.find("--") != string::npos) {
        ok = 0;
    }


    char last = s.back();
    int dig;
    if(last == 'X') {
        dig = 10;
    } else {
        dig = last - '0';
    }
    s.pop_back();

    // cout << "dig : " << dig << '\n';
    // cout << "ok3 : " << ok << endl;

    //gotta have a hyphen in the back
    if(count(s.begin(), s.end(), '-') == 3 && s.back() != '-') {
        ok = 0;
    }

    //no more x's in the string, please. 
    if(s.find("X") != string::npos) {
        ok = 0;
    }

    // cout << "ok4 : " << ok << endl;

    vector<int> a;
    for(char c : s) {
        if('0' <= c && c <= '9') {
            a.push_back(c - '0');
        }
    }

    if(a.size() != 9) ok = 0;

    // cout << "ok a size : " << ok << endl;
    // cout << "a size : " << a.size() << endl;

    int sum = 0;
    for(int i = 0; i < a.size(); i++) {
        sum += (10 - i) * a[i];
    }

    if((sum + dig) % 11) {
        // cout << "bad sum : " << sum % 11 << " dig : " << dig << endl;
        ok = 0;
    }

    // cout << "ok checksum : " << ok << endl;

    if(ok == 0) {
        cout << "invalid\n";
        return;
    }

    string res = "";
    sum = 0;
    int p = 1;

    res.push_back('9');
    sum += 9;
    res.push_back('7');
    sum += 7 * 3;
    res.push_back('8');
    sum += 8;
    res.push_back('-');

    for(char c : s) {
        if('0' <= c && c <= '9') {
            if(p == 1) {
                sum += 3 * (c - '0');
            } else {
                sum += c - '0';
            }
            p ^= 1;
        }
        res.push_back(c);
    }

    res.push_back('0' + (((10 - sum) % 10) + 10) % 10);
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << (10 * 0 + 9 * 3 + 8 * 9 + 7 * 4 + 6 * 2 + 5 * 8 + 4 * 0 + 3 * 1 + 2 * 3) % 11 << endl;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}