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
    int num = 0;
    for(int i = 0; i < s.size(); i++) {
        num *= 8;
        num += s[i] - '0';
    }

    vector<vector<int>> board(3, vector<int>(3, -1));

    for(int i = 0; i < 9; i++) {
        if((num >> i) & 1) {
            int row = i / 3, col = i % 3;
            board[row][col] = (num >> (i + 9)) & 1;
        }
    }

    int state = -1;

    auto upd = [&](vector<array<int,2>> pos) -> void {
        int ok = 1;
        for(int i = 1; i < pos.size(); i++) {
            int prev = board[pos[i-1][0]][pos[i-1][1]];
            int nx = board[pos[i][0]][pos[i][1]];
            if(prev == nx && nx != -1) {

            } else {
                ok = 0;
            }
        }
        if(ok) {
            state = board[pos[0][0]][pos[0][1]];
        }
    };

    for(int i = 0; i < 3; i++) {
        int ok = 1;
        vector<array<int,2>> pos;
        for(int j = 0; j < 3; j++) {
            pos.push_back({i, j});
        }
        upd(pos);
        pos.clear();
        for(int j = 0; j < 3; j++) {
            pos.push_back({j, i});
        }
        upd(pos);
    }

    vector<array<int,2>> check = {
        {0,0},
        {1,1},
        {2,2}
    };

    vector<array<int,2>> check2 = {
        {2,0},
        {1,1},
        {0,2}
    };

    upd(check);
    upd(check2);

    if(state != -1) {
        cout << (state ? 'X' : 'O') << " wins\n";
    } else {
        int inp = 0;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == -1) inp = 1;
            }
        }
        cout << (inp ? "In progress" : "Cat's") << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}