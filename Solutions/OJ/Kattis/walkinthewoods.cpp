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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        for(auto &x : a[i]) cin >> x;
    }
    vector<vector<array<int,2>>> adj(n, vector<array<int,2>>(4, {-1, 0})); // {dest, cnt}

    //direction when going from node i to node j. 
    auto get_dir = [&](int i, int j) -> int {
        auto [xi, yi] = a[i];
        auto [xj, yj] = a[j];
        if(yi < yj) return 0;
        if(xi < xj) return 1;
        if(yi > yj) return 2;
        if(xi > xj) return 3;
        cout << "i : " << i << " j : " << j << endl;
        assert(0);
    };

    for(int t = 0; t < m; t++) {
        int i, j, k; cin >> i >> j >> k;
        i--; j--;

        // cout << "i : " << i << " j : " << j << " k : " << k << endl;

        int dirij = get_dir(i, j);
        adj[i][dirij] = {j, k};
        int dirji = get_dir(j, i);
        adj[j][dirji] = {i, k};
    }

    int start; cin >> start;
    start--;
    char ch; cin >> ch;
    int dir;
    if(ch == 'N') {
        dir = 0;
    } else if(ch == 'E') {
        dir = 1;
    } else if(ch == 'S') {
        dir = 2;
    } else if(ch == 'W') {
        dir = 3;
    } else {
        assert(0);
    }

    int boom = 0;

    //actually goes. 
    auto go = [&](int cur, int dir, int take_cnt) -> array<int,2> {
        int j = adj[cur][dir][0];
        assert(adj[cur][dir][1] >= take_cnt);
        if(adj[cur][dir][1] == take_cnt) boom = 1;
        adj[cur][dir][1] -= take_cnt;
        adj[j][dir ^ 2][1] -= take_cnt;
        cur = j;
        return {j, dir};
    };

    auto pp = [&](int i) -> void {
        cout << "pos : " << a[i][0] << ", " << a[i][1] << endl;
    };

    int cur;

    {
        auto [nx, nxdir] = go(start, dir, 1);
        cur = nx;
    }

    // cout << "starting position\n";
    // pp(cur);

    //given that i am at point cur and facing dir, returns the direction of the path i will take and its destination, {-1,-1} if bad. 
    auto sim = [&](int cur, int dir) -> array<int,2> {
        vector<array<int,2>> moves; // {direction, destination}
        for(int i = 3; i < 6; i++) {
            int nx_dir = (dir + i) % 4;
            if(adj[cur][nx_dir][1]) {
                moves.push_back({nx_dir, adj[cur][nx_dir][0]});
            }
        }   
        if(moves.empty()) return {-1,-1};
        if(moves.size() == 3) {
            return moves[1];
        } else {
            return moves[0];
        }
    };

    // vector<vector<int>> vis;

    while(1) {

        //we will sim until either we reach a dead end or reach a cycle. 
        set<array<int,2>> vis;
        map<array<int,2>, int> m;

        // cout << "prev cur\n";
        // pp(cur);

        int prev_start = cur, prev_dir = dir;

        //now, we will go until either 1) we revisit a node in the cycle or 2) we reach a dead end. 
        while(1) {
            if(vis.count({cur, dir})) break;
            vis.insert({cur, dir});
            auto [nx_dir, nx_cur] = sim(cur, dir);
            // cout << "next sim\n";
            // pp(nx_cur);
            if(nx_cur == -1) break; //we break before the dead end. 
            m[{min(cur, nx_cur),max(cur, nx_cur)}]++;
            assert(cur != nx_cur);
            cur = nx_cur, dir = nx_dir;
        }

        // cout << "after revisit cur\n";
        // pp(cur);

        boom = 0;
        swap(cur, prev_start);
        swap(dir, prev_dir);

        //we moved up cur, now we bring the previous stuff up to speed. 
        //we will go until we destroy an edge or reach our starting point or reach a dead end. 
        while((prev_start != cur || prev_dir != dir) && boom == 0) {
            auto [nx_dir, nx_cur] = sim(cur, dir);
            assert(nx_dir >= 0);
            m[{min(cur, nx_cur), max(cur, nx_cur)}]--;
            assert(cur != nx_cur);
            go(cur, nx_dir, 1);
            cur = nx_cur;
            dir = nx_dir;
        }

        //now prev_start is up to speed
        if(boom) continue;

        //if there are no more moves possible ... 
        {
            auto [nx_dir, nx_cur] = sim(cur, dir);
            if(nx_cur == -1) break;
        }

        int cycle_cnt = INT_MAX;

        //maximum cycles we can take now. 
        for(auto [k, v] : m) {
            if(v) {
                auto [i, j] = k;
                // cout << "kv i : " << i << " j : " << j << endl;
                int dir = get_dir(i, j);
                cycle_cnt = min(cycle_cnt, adj[i][dir][1] / v);
            }
        }

        // cout << "cycle_cnt : " << cycle_cnt << endl;

        boom = 0;

        //take out the cycles, we should still be in the same position. 
        for(auto [k, v] : m) {
            auto [i, j] = k;
            int dirij = get_dir(i, j);
            go(i, dirij, cycle_cnt * v);
        }

        while(boom == 0) {
            auto [nx_dir, nx_cur] = sim(cur, dir);
            if(nx_dir == -1) break;
            go(cur, nx_dir, 1);
            cur = nx_cur;
            dir = nx_dir;
        }

        assert(boom);
    }

    // cout << "cur : " << cur << endl;
    // pp(cur);
    cout << a[cur][0] << " " << a[cur][1] << endl;

    return 0;
}
