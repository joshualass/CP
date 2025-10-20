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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

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

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    map<string,ll> key; //map string to ll
    map<ll,string> val; //map ll back to string
    vector<ll> started; //intervals that haven't been started yet. 
    set<int> singles;

    vector<array<ll,5>> hashes; //hashes for each of the llervals
    set<array<ll,5>> unvis_states; //unvisted states from the input
    map<ll,ll> double_cnts; //how many times this name appears in a double

    auto add_to_hash = [&](array<ll,5> &curr_hash, ll id_to_add, ll mult) -> void {
        for(ll i = 0; i < 5; i++) curr_hash[i] += hashes[id_to_add][i] * mult;
    };

    for(ll i = 0; i < n; i++) {
        ll sz; cin >> sz;
        array<ll,5> cur_hash = {};
        vector<ll> a;
        for(ll j = 0; j < sz; j++) {
            string name; cin >> name;
            if(key.count(name) == 0) {
                ll id = key.size();
                key[name] = id;
                val[id] = name;
                array<ll,5> h = {};
                for(ll k = 0; k < 5; k++) {
                    h[k] = rng() % 1000000000;
                }
                hashes.push_back(h);
                started.push_back(0);
            }
            ll id = key[name];
            a.push_back(id);
            add_to_hash(cur_hash, id, 1);
        }
        unvis_states.insert(cur_hash);
        // cout << "i : " << i << " hash : " << cur_hash << '\n';
        if(a.size() == 2) {
            for(ll id : a) {
                double_cnts[id]++;
            }
        }
        if(a.size() == 1) singles.insert(a[0]);
    }

    // cout << "uvis sz : " << unvis_states.size() << '\n';
    // cout << "unvis_states : " << unvis_states << '\n';

    // cout << "key\n";
    // for(auto [u, v] : key) cout << u << ", " << v << '\n';

    // cout << "hashes : " << hashes << '\n';

    // cout << "singles\n";
    // for(int x : singles) {
    //     cout << "x : " << x << " name : " << val[x] << '\n';
    // }

    ll ok = 1, cur = 0, need_start = 0;
    vector<ll> res, coord;

    auto start = [&](array<ll,5> &curr_hash, deque<ll> &dq, ll v) -> void {
        // cout << "start called with val : " << v << " name : " << val[v] << '\n';
        if(started[v]) {
            // cout << "not ok started[v] : " << v << '\n';
            ok = 0;
        }
        started[v] = 1;
        add_to_hash(curr_hash, v, 1);
        dq.push_back(v);
        res.push_back(v);
        coord.push_back(cur++);
        need_start = 0;
        if(unvis_states.count(curr_hash) == 0) {
            // cout << "unvis hash dne\n";
            ok = 0;
        }
        unvis_states.erase(curr_hash);
    };

    auto end = [&](array<ll,5> &curr_hash, deque<ll> &dq) -> void {
        assert(dq.size());
        ll to_remove = dq[0];
        // cout << "ending now, removing : " << to_remove << "\n";
        add_to_hash(curr_hash, to_remove, -1);
        if(need_start) {
            // cout << "ok by need start false\n";
            ok = 0;
        }
        res.push_back(to_remove);
        if(curr_hash == array<ll,5>{0,0,0,0,0} || unvis_states.count(curr_hash)) {
            unvis_states.erase(curr_hash);
            coord.push_back(cur++);
        } else {
            coord.push_back(cur);
            // cout << "ending but next set is not found!\n";
            need_start = 1;
        }
        dq.pop_front();
    };

    while(double_cnts.size()) {
        auto [id, freq] = *double_cnts.begin();
        double_cnts.erase(double_cnts.begin());
        if(freq != 1 || started[id] || singles.count(id) == 0) {
            continue;
        }

        // cout << "id : " << id << " real name : " << val[id] << " freq : " << freq << '\n';

        array<ll,5> curr_hash = {}; //current set
        deque<ll> dq; //current dq

        // cout << "start ch : " << curr_hash << '\n';

        // cout << "start id : " << id << '\n';

        start(curr_hash, dq, id);
        while(dq.size()) {
            //try appending all possible things
            ll f = -1;
            for(ll i = 0; i < hashes.size(); i++) {
                if(started[i] == 0) {
                    //try adding and seeing if its in the set. 
                    // cout << "try starting with i : " << i << "\n";
                    add_to_hash(curr_hash, i, 1);
                    if(unvis_states.count(curr_hash)) {
                        f = i;
                    }
                    add_to_hash(curr_hash, i, -1);
                }
            }
            // cout << "f : " << f << '\n';
            // cout << "ns : " << need_start << '\n';
            //we have to remove, can't add ...
            if(f == -1) {
                end(curr_hash, dq);
            } else {
                start(curr_hash, dq, f);
            }
        }
    }

    for(ll i = 0; i < hashes.size(); i++) {
        if(started[i] == 0) {
            array<ll,5> curr_hash = {};
            deque<ll> dq;
            start(curr_hash, dq, i);
            end(curr_hash, dq);
        }
    }

    // cout << "ok up to here 5 : " << ok << "\n";

    if(unvis_states.size()) ok = 0;
    // cout << "remaining unvis states : " << unvis_states << '\n';
    if(accumulate(started.begin(), started.end(), 0) != hashes.size()) ok = 0;

    if(ok) {
        map<string,vector<ll>> ans;
        for(ll i = 0; i < res.size(); i++) {
            ans[val[res[i]]].push_back(coord[i]);
        }
        for(auto [k, v] : ans) {
            cout << k << " " << v[0] << " " << v[1] << '\n';
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}

/*

5
1 A
2 A B
3 A B C
2 B C
1 C

5
1 A
2 A B
1 B
2 B D
1 D

7
1 A
2 A B
2 B C
1 C
2 C D
2 D E
1 E

9
1 Z
2 Z A
3 Z A B
2 A B
2 B C
1 C
2 C D
2 D E
1 E


6
1 A
2 A B
2 B C
2 C D
2 D E
1 E

9
1 A
2 A B
3 A B C
4 A B C D
5 A B C D E
4 B C D E
3 C D E
2 D E
1 E


*/