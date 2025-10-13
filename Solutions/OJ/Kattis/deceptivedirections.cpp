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

    int m, n;
    cin >> m >> n;
    vector<string> g(n);
    for(int i = 0; i < n; i++) cin >> g[i];
    string s;
    cin >> s;
    vector<vector<bool>> v(n, vector<bool>(m, false));
    queue<pair<int, int>> q;
    vector<vector<int>> bd(n, vector<int>(m, 1e9));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(g[i][j] == 'S') {
        v[i][j] = true;
        q.push({i, j});
        bd[i][j] = 0;
    }
    string dir = "NESW";
    vector<int> dr = {-1, 0, 1, 0}, dc = {0, 1, 0, -1};
    for(int i = 0; i < s.size(); i++) {
        queue<pair<int, int>> nq;
        while(q.size() != 0) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            for(int j = 0; j < 4; j++) {
                int nr = r + dr[j];
                int nc = c + dc[j];
                if(v[nr][nc]) continue;
                if(g[nr][nc] == '#') continue;
                if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                if(dir[j] == s[i]) continue;
                v[nr][nc] = true;
                bd[nr][nc] = bd[r][c] + 1;
                nq.push({nr, nc});
            }
        }
        q = nq;
    }
    while(q.size() != 0) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        g[r][c] = '!';
    }
    vector<vector<int>> d(n, vector<int>(m, 1e9));
    assert(q.size() == 0);
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(g[i][j] == 'S') {
        q.push({i, j});
        d[i][j] = 0;
    }
    while(q.size()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(g[nr][nc] == '#') continue;
            if(d[nr][nc] != 1e9) continue;
            
            d[nr][nc] = d[r][c] + 1;
            if(d[nr][nc] != bd[nr][nc]) g[nr][nc] = '.';
            q.push({nr, nc});
        }
    }
    for(int i = 0; i < n; i++) cout << g[i] << "\n";

    return 0;
}
