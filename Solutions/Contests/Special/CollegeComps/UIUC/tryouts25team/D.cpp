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
    vector<vector<int>> ch(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        ch[p].push_back(i);
    }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " ch[i] : " << ch[i] << '\n';
    // }

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> flow_min(n, 0);
    vector<int> can_inc(n);
    vector<ll> need_here(n);

    for(int i = n - 1; i >= 0; i--) {
        if(a[i]) {
            flow_min[i] = a[i];
        } else {
            //leaf
            if(ch[i].empty()) {
                can_inc[i] = 1;
                flow_min[i] = 1;
            } else {
                for(int c : ch[i]) {
                    flow_min[i] += flow_min[c];
                    can_inc[i] |= can_inc[c];
                }
            }
        }
    }

    // cout << "flow_min : " << flow_min << '\n';
    // cout << "can_inc : " << can_inc << '\n';

    int bad = 0;
    for(int i = 0; i < n; i++) {

        if(i) {
            // cout << "i : " << i << " need_here[i] : " << need_here[i] << '\n';

            if(a[i] != 0 && a[i] != need_here[i]) {
                bad = 1;
                // cout << "bad3\n";
                break;
            }

            if(ch[i].empty()) continue;

            if(flow_min[i] > need_here[i]) {
                bad = 1;
                // cout << "bad4\n";
                break;
            }

            ll ch_mins = 0;
            for(int c : ch[i]) ch_mins += flow_min[c];

            if(ch_mins == need_here[i]) {
                for(int c : ch[i]) {
                    need_here[c] = flow_min[c];
                }
            } else {
                // cout << "i : " << i << " need_here [i] : " << need_here[i] << " min[i] : " << ch_mins << '\n';
                vector<int> ch_adj;
                for(int c : ch[i]) {
                    if(can_inc[c]) {
                        ch_adj.push_back(c);
                    }
                }
                if(ch_adj.size() != 1) {
                    bad = 1;
                    // cout << "bad5\n";
                    break;
                }
                for(int c : ch[i]) {
                    need_here[c] = flow_min[c];
                }
                ll extra = need_here[i] - ch_mins;
                need_here[ch_adj[0]] += extra;
            }


        } else {
            //there exists a path from leaf to root of all 0's
            if(can_inc[i]) {
                // cout << "bad0\n";
                bad = 1;
                break;
            }

            ll ch_mins = 0;
            for(int c : ch[i]) ch_mins += flow_min[c];
            
            //none of the child paths can move, this is fixed to flow_min
            if(a[i] == 0) {
                need_here[i] = flow_min[i];
                for(int c : ch[i]) {
                    need_here[c] = flow_min[c];
                }
            } else {
                need_here[i] = a[i];
                //child flows too much!
                if(ch_mins > a[i]) {
                    bad = 1; 
                    // cout << "bad1\n";
                    break;
                }
                //perfect match
                if(ch_mins == need_here[i]) {
                    for(int c : ch[i]) {
                        need_here[c] = flow_min[c];
                    }
                } else {
                    //have some excess, need to dump to precisely one child
                    vector<int> ch_adj;
                    for(int c : ch[i]) {
                        if(can_inc[c]) {
                            ch_adj.push_back(c);
                        }
                    }
                    if(ch_adj.size() != 1) {
                        bad = 1;
                        // cout << "bad2\n";
                        break;
                    }
                    //dump the excess to precisely one of the children. 
                    for(int c : ch[i]) {
                        need_here[c] = flow_min[c];
                    }
                    ll extra = a[i] - ch_mins;
                    // cout << "extra : " << extra << " ch : " << ch_adj[0] << '\n';
                    need_here[ch_adj[0]] += extra;
                }
            }
            // cout << "i : " << i << " need_here[i] : " << need_here[i] << '\n';
        }
    }

    // cout << "need here : " << need_here << '\n';


    if(bad) {
        cout << "impossible\n";
        return 0;
    }

    for(int i = 0; i < n; i++) cout << need_here[i] << '\n';

    return 0;
}
