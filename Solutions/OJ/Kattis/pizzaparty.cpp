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

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    cin.ignore();
    vector<pair<set<string>, string>> ors, ands;
    set<string> vis;
    queue<string> q;
    auto add_q = [&](string s) -> void {
        // cout << "add q s : " << s << '\n';
        if(vis.count(s)) return;
        vis.insert(s);
        q.push(s);
    };

    for(int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        vector<string> tokens;
        while(!ss.eof()) {
            string s; ss >> s;
            tokens.push_back(s);
        }
        if(tokens.size() == 1) {
            add_q(tokens[0]);
        } else {
            set<string> p;
            for(int i = 1; i + 1 < tokens.size(); i += 2) p.insert(tokens[i]);
            string res = tokens.back();
            if(tokens.size() >= 6 && tokens[2] == "or") {
                ors.push_back({p, res});
            } else {
                ands.push_back({p, res});
            }
        }
    }

    // for(int i = 0; i < ors.size(); i++) {
    //     cout << "i : " << i << " ors[i] set : " << ors[i].first << " targ : " << ors[i].second << '\n';
    // }

    // for(int i = 0; i < ands.size(); i++) {
    //     cout << "i : " << i << " ands[i] set : " << ands[i].first << " targ : " << ands[i].second << '\n';
    // }

    while(q.size()) {
        string s = q.front();
        q.pop();

        for(int i = 0; i < ands.size(); i++) {
            ands[i].first.erase(s);
            if(ands[i].first.empty()) add_q(ands[i].second);
        }

        for(int i = 0; i < ors.size(); i++) {
            if(ors[i].first.count(s)) ors[i].first.clear();
            if(ors[i].first.empty()) add_q(ors[i].second);
        }

    }

    cout << vis.size() << '\n';

    return 0;
}
