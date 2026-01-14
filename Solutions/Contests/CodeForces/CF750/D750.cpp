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

int vis[400][400], dp[400][400][8], ndp[400][400][8];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> dx = {1, 1, 0, -1, -1, -1, 0, 1}, dy = {0, 1, 1, 1, 0, -1, -1, -1};

    dp[200][200][0] = 1;

    for(int i = 0; i < n; i++) {
        memset(ndp, 0, sizeof(ndp));
        for(int j = 0; j < 400; j++) {
            for(int k = 0; k < 400; k++) {
                for(int dir = 0; dir < 8; dir++) {
                    if(dp[j][k][dir]) {
                        int cx = j, cy = k;
                        vis[cx][cy] = 1;
                        for(int l = 1; l < a[i]; l++) {
                            cx += dx[dir];
                            cy += dy[dir];
                            vis[cx][cy] = 1;
                        }

                        int dir1 = (dir + 7) % 8;
                        int tx1 = cx + dx[dir1];
                        int ty1 = cy + dy[dir1];
                        ndp[tx1][ty1][dir1] = 1;

                        int dir2 = (dir + 1) % 8;
                        int tx2 = cx + dx[dir2];
                        int ty2 = cy + dy[dir2];
                        ndp[tx2][ty2][dir2] = 1;

                    }
                }
            }

        }

        for(int j = 0; j < 400; j++) {
            for(int k = 0; k < 400; k++) {
                for(int l = 0; l < 8; l++) {
                    dp[j][k][l] = ndp[j][k][l];
                }
            }
        }
    }

    int res = 0;

    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 400; j++) {
            if(vis[i][j]) res++;
        }
    }

    cout << res << '\n';

    return 0;
}
