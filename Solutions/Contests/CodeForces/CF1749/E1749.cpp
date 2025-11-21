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
    
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<int>> dists(n, vector<int>(m, 1e9));
    vector<vector<array<int,2>>> pars(n, vector<array<int,2>>(m, {-1,-1}));
    priority_queue<array<int,5>, vector<array<int,5>>, greater<array<int,5>>> pq;

    auto push_q = [&](int x, int y, int dist, int px, int py) {
        // cout << "push q called x : " << x << " y : " << y << " dist : " << dist << " px : " << px << " py : " << py << '\n';
        if(a[x][y] == '.') dist++;
        //check if we can push
        vector<int> dx = {1,-1,0,0}, dy = {0,0,1,-1};
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == '#') return; //adjacent cactus is here
        }
        // cout << "cactus check ok!\n";
        //ok, we can consider adding this to the queue
        if(dist < dists[x][y]) {
            // cout << "better dist ok push to queue!\n";
            dists[x][y] = dist;
            pq.push({dist, x, y, px, py});
        }
    };

    for(int i = 0; i < n; i++) push_q(i, 0, 0, -1, -2);

    vector<int> dx = {1,1,-1,-1}, dy = {1,-1,1,-1};

    while(pq.size()) {
        auto [d, x, y, px, py] = pq.top();
        pq.pop();
        if(pars[x][y] != array<int,2>{-1,-1}) continue;
        pars[x][y] = {px, py};
        // cout << "d : " << d << " x : " << x << " y : " << y << " px : " << px << " py : " << py << '\n';
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m) push_q(nx, ny, d, x, y);
        }
    }

    int res = 1e9;
    int sx = -1, sy = -1;
    for(int i = 0; i < n; i++) {
        if(dists[i][m-1] < res) {
            res = dists[i][m-1];
            sx = i;
            sy = m - 1;
        }
    }

    if(sx == -1) {
        cout << "NO\n";
        return;
    }

    while(sx != -1) {
        a[sx][sy] = '#';
        auto nx = pars[sx][sy];
        sx = nx[0], sy = nx[1];
    }

    cout << "YES\n";
    for(auto x : a) cout << x << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}