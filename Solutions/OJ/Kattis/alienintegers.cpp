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

//return -1 if none exists
ll gen_top(string s, set<int> av) {
    int fdig = -1;
    for(int i = s[0] - '0' + 1; i < 10; i++) {
        if(av.count(i)) {
            fdig = i;
            break;
        }
    }
    int ldig = -1;
    for(int i = 0; i < 10; i++) {
        if(av.count(i)) {
            ldig = i;
            break;
        }
    }
    assert(ldig != -1);
    if(fdig != -1) {
        assert(fdig != 0);
        string x(s.size(), '.');
        x[0] = '0' + fdig;
        for(int i = 1; i < s.size(); i++) x[i] = '0' + ldig;
        return stoll(x);
    }
    //can't find first digit
    int nzdig = -1;
    for(int i = 1; i < 10; i++) {
        if(av.count(i)) {
            nzdig = i;
            break;
        }
    }
    assert(nzdig != -1);
    string x(s.size() + 1, '.');
    x[0] = '0' + nzdig;
    for(int i = 1; i < s.size() + 1; i++) x[i] = '0' + ldig;
    return stoll(x);
}

//return -1 if none exists
ll gen_bot(string s, set<int> av) {
    if(s == "0") return -1;
    int fdig = -1;
    for(int i = 1; i < s[0] - '0'; i++) {
        if(av.count(i)) {
            fdig = i;
        }
    }
    if(s.size() == 1 && av.count(0) && fdig == -1) fdig = 0;
    int ldig = -1;
    for(int i = 9; i >= 0; i--) if(av.count(i)) {
        ldig = i;
        break;
    }
    assert(ldig != -1);
    // cout << "BOT FDIG : " << fdig << "\n";
    if(fdig != -1) {
        string x(s.size(), '.');
        x[0] = '0' + fdig;
        for(int i = 1; i < s.size(); i++) {
            x[i] = '0' + ldig;
        }
        return stoll(x);
    }
    //can't find first digit, need to shorten
    //put highest element we can
    if(s.size() == 1) return -1;    //can't shorten
    string x(s.size() - 1, '.');
    for(int i = 0; i < x.size(); i++) x[i] = '0' + ldig;
    return stoll(x);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    set<int> avs;
    for(int i = 0; i < 10; i++) {
        avs.insert(i);
    }
    for(int i = 0; i < n; i++) {
        int dig = s[i] - '0';
        if(avs.count(dig)) avs.erase(dig);
    }
    if(avs.size() == 0) {
        cout << "Impossible\n";
        return 0;
    }
    if(avs.size() == 1 && avs.count(0)) {
        //only 0
        cout << "0\n";
        return 0;
    }
    //ok, we should have some non-zero digit to work with
    ll top = gen_top(s, avs);
    ll bot = gen_bot(s, avs);
    // cout << "TOP BOT : " << top << " " << bot << "\n";
    assert(top != -1);
    assert(!(top == -1 && bot == -1));
    if(top == -1) cout << bot << "\n";
    else if(bot == -1) cout << top << "\n";
    else {
        ll val = stoll(s);
        if(abs(val - top) == abs(val - bot)) cout << bot << " " << top << "\n";
        else if(abs(val - top) < abs(val - bot)) cout << top << "\n";
        else cout << bot << "\n";
    }

    return 0;
}
