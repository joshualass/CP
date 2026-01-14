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
    
    int n, q; cin >> n >> q;
    string s; cin >> s;
    int empty_pairs = 0, total_score = 0, trash_singles = 0, I_opps = 0, VX_opps = 0, IVX_opps = 0;

    auto add_seg = [&](int prev_idx, int cur_idx) {

        char p = (prev_idx == -1 ? 'V' : s[prev_idx]);
        char cur = (cur_idx < n ? s[cur_idx] : '?');
        char nx = (cur_idx + 1 < n ? s[cur_idx + 1] : 'I');

        int i_good, vx_good;
        if(cur == 'I') {
            if(nx == 'X' || nx == 'V') {
                total_score--;
            } else {
                total_score += 1;
            } 
            i_good = 0;
        } else if(cur == 'V') {
            total_score += 5;
            i_good = 1;
        } else if(cur == 'X') {
            total_score += 10;
            i_good = 1;
        } else {
            i_good = 0;
        }

        vx_good = p == 'I';
        int len = cur_idx - prev_idx - 1;

        if(len == 0) return;

        if(i_good && vx_good) {
            if(len & 1) {
                IVX_opps++;
                len--;
            } else {
                I_opps++;
                VX_opps++;
                len -= 2;
            }
            empty_pairs += len / 2;
        } else {
            if(i_good) {
                I_opps++;
                len--;
            }
            if(vx_good) {
                VX_opps++;
                len--;
            }
            empty_pairs += len / 2;
            trash_singles += len & 1;
        }
    };

    int p = -1;

    for(int i = 0; i < n; i++) {
        if(s[i] != '?') {
            add_seg(p, i);
            p = i;
        }
    }

    add_seg(p, n);
    int q_cnt = count(s.begin(), s.end(), '?');

    // cout << "ep : " << empty_pairs << " total score : " << total_score << " trash_singles : " << trash_singles << " I ops : " << I_opps << " VX ops : " << VX_opps << " IVX ops : " << IVX_opps << '\n';

    for(int qq = 0; qq < q; qq++) {
        int x, v, i; cin >> x >> v >> i;
        int total = x + v + i;

        int rx = min(x, total - q_cnt);
        x -= rx;
        total -= rx;

        int rv = min(v, total - q_cnt);
        v -= rv;
        total -= rv;

        int ri = min(i, total - q_cnt);
        i -= ri;
        total -= ri;

        int res = total_score + x * 10 + v * 5 + i;
        int sub = 0;
        // cout << "rx : " << rx << " rv : " << rv << " ri " << ri << '\n';
        // cout << "starting res : " << res << '\n';
        // cout << "in use i : " << i << " v : " << v << " x : " << x << '\n';

        //greedily remove as many pairs as possible
        //remove as many I_opps / VX_opps as possible
        ri = min(I_opps, i);
        sub += ri;
        i -= ri;

        int t = VX_opps;

        rv = min(t, v);
        sub += rv;
        v -= rv;
        t -= rv;

        rx = min(t, x);
        sub += rx;
        x -= rx;

        //remove as many pairs as possible
        int rp = min({empty_pairs, i, v + x});
        sub += rp;
        res -= IVX_opps * 2;

        cout << res - sub * 2 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}