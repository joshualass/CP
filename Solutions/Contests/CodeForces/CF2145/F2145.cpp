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

/*

N : 2
M : 10
A : 8 8 
B : 5 3 
solve slow : 11 solve fast : 12


*/

/*

implementation felt a little wishy washy. 

was missing the edge case for when it is not optimal to complete a cycle because it may include some extra stalling turns even the the cycle puts us not after 
the final right position. could also make observations a little faster + impl better ...
we should try to do one less cycle possible ... 

*/

int test_mode = 0;
ll res_slow, res_fast;
vector<int> A, B;
ll N, M;

int vis[2520][2520];

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int solve_id_vis[2520][10], attime[2520][10], atpos[2520][10];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve(int solve_id) {
    ll n, m; 
    vector<int> a, b;
    if(test_mode) {
        n = N, m = M;
        a = A, b = B;
    } else {
        cin >> n >> m;
        a.assign(n, 0);
        b.assign(n, 0);
        for(int &x : a) cin >> x;
        for(int &x : b) cin >> x;
    }
    
    int l = 1;
    for(int x : a) l = lcm(l, x);

    int first_pos, first_time, last_pos, last_time;

    {
        int pos = 0, time = 0;
        // cout << "start while1" << endl;
        while(1) {
            if((pos + 1) % a[time % n] != b[time % n]) {
                pos++;
            }
            time++;
            if(solve_id_vis[pos % l][time % n] == solve_id) {
                first_pos = atpos[pos % l][time % n];
                first_time = attime[pos % l][time % n];
                last_pos = pos;
                last_time = time;
                break;
            }
            solve_id_vis[pos % l][time % n] = solve_id;
            attime[pos % l][time % n] = time;
            atpos[pos % l][time % n] = pos;
        }
    }

    // cout << "first pos : " << first_pos << " last pos : " << last_pos << '\n';
    // cout << "first time : " << first_time << " last time : " << last_time << '\n';

    // cout << "end while1" << endl;

    auto sim = [&](ll &start_time, ll &start_pos, ll end_pos) -> void {
        // cout << "start sim" << endl;
        // cout << "start_time : " << start_time << " start_pos : " << start_pos << " end_pos : " << end_pos << endl;
        // cout << "a : " << a << endl;
        // cout << "b : " << b << endl;
        while(start_pos < end_pos) {
            // cout << "start_pos : " << start_pos << " start time : " << start_time << endl;
            if((start_pos + 1) % a[start_time % n] != b[start_time % n]) {
                start_pos++;
            }
            start_time++;
        }
        // cout << "end sim" << endl;
    };

    ll cur_pos = 0, cur_time = 0;
    sim(cur_time, cur_pos, min(m, (ll) first_pos));

    //done early. we should always be able to sim up to first pos. 
    if(cur_pos == m) {
        if(test_mode) {
            res_fast = cur_time;
        } else {
            cout << cur_time << '\n';
        }
        return;
    }

    //match up time
    while(cur_time % n != first_time % n) cur_time++;

    //simulate as many periods as we can
    ll period_time = last_time - first_time;
    ll period_dist = last_pos - first_pos;

    //we get stuck after simulating to our period starting point, this is impossible!
    if(period_dist == 0) {
        if(test_mode) {
            res_fast = -1;
        } else {
            cout << "-1\n";
        }
        return;
    }

    ll cycles = max(0LL, (m - cur_pos) / period_dist - 1);

    //simulate the cycles
    cur_pos += cycles * period_dist;
    cur_time += cycles * period_time;

    //finally, sim to the end
    sim(cur_time, cur_pos, m);

    if(test_mode) {
        res_fast = cur_time; 
    } else {
        cout << cur_time << '\n';
    }

}

void solve_slow() {
    ll n = N, m = M;
    vector<int> a = A, b = B;

    int pos = 0, time = 0;
    int mx = n * m * 2;
    while(pos < m) {
        if((pos + 1) % a[time % n] != b[time % n]) pos++;
        time++;
        if(time >= mx) {
            res_slow = -1;
            return;
        }
    }

    res_slow = time;

}

int test(vector<int> a, vector<int> b, int test_id) {
    int n = a.size();
    int l = 1;
    for(int x : a) l = lcm(l, x);

    int pos = 0, time = 0;
    while(1) {
        if((pos + 1) % a[time % n] != b[time % n]) {
            pos++;
        }
        if(vis[pos % l][time % l] == test_id) return time;
        vis[pos % l][time % l] = test_id;
        time++;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(test_mode) {

        for(int tc = 1; tc <= 10000; tc++) {
            N = 10;
            M = rng() % 10000 + 1;
            A.assign(N, 0);
            B.assign(N, 0);
            for(int j = 0; j < N; j++) {
                A[j] = (rng() % 9) + 2;
                B[j] = rng() % A[j];
            }

            // cout << "A : " << A << '\n';
            // cout << "B : " << B << '\n';

            solve_slow();
            solve(tc);

            if(res_slow != res_fast) {
                cout << "N : " << N << '\n';
                cout << "M : " << M << '\n';
                cout << "A : " << A << "\n";
                cout << "B : " << B << "\n";
                cout << "solve slow : " << res_slow << " solve fast : " << res_fast << endl;
                assert(0);
            } else {
                // cout << "solve slow : " << res_slow << " solve fast : " << res_fast << endl;
            }
        }

        cout << "all tests passed!" << endl;

        //what was bro doing lol ...
        //100 testcases runs very fast . 
        // int tc; cin >> tc;
        // for(int i = 0; i < tc; i++) {
        //     vector<int> a(10), b(10);
        //     for(int j = 0; j < 10; j++) {
        //         a[j] = max(2, j + 1);
        //         b[j] = rng() % a[j];
        //     }
        //     cout << "test : " << test(a, b, i + 1) << '\n';
        // }
    
        // int l = 1;
        // for(int i = 1; i <= 10; i++) l = lcm(l, i);
        // cout << l << '\n';
    } else {
        int casi; cin >> casi;
        for(int solve_id = 1; solve_id <= casi; solve_id++) solve(solve_id);
        // while(casi-->0) solve();
    }


    return 0;
}