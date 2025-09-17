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
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K; cin >> n >> K;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector pc(n, vector(K + 1, vector(2, array<int,2>{-1,-1})));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i].size(); j++) {
            for(int k = 0; k < 2; k++) {
                string cur = a[i].substr(0, j);
                cur.push_back('(' + k);
                int bad = 0;
                for(string s : a) {
                    if(cur.find(s) != string::npos) bad = 1;
                }
                if(bad) continue;
                int nx = i, len = 0;
                for(int l = 0; l < n; l++) {
                    for(int m = 1; m <= min(a[l].size(), cur.size()); m++) {
                        if(cur.substr(cur.size() - m) == a[l].substr(0, m)) {
                            if(m > len) {
                                nx = l;
                                len = m;
                            }
                        }
                    }
                }
                pc[i][j][k] = {nx, len};
            }
        }
    }

    vector dp(K + 1, vector(K / 2 + 1, vector(n, vector(K + 1, array<int,3>{-1,-1,-1}))));

    dp[0][0][0][0] = {0,0,0};
    for(int i = 0; i < K; i++) {
        for(int j = 0; j <= K / 2; j++) {
            for(int k = 0; k < n; k++) {
                for(int l = 0; l <= a[k].size(); l++) {
                    if(dp[i][j][k][l] != array<int,3>{-1,-1,-1}) {
                        // cout << "vis i : " << i << " j : " << j << " k : " << k << " l : " << l << '\n';
                        for(int m = 0; m < 2; m++) {
                            int nxi = i + 1;
                            int nxj = j + (m ? -1 : 1);
                            auto [nxk, nxl] = pc[k][l][m];
                            if(0 <= nxj && nxj <= K / 2 && nxk != -1) {
                                dp[nxi][nxj][nxk][nxl] = {j, k, l};
                            }
                        }
                    }
                }
            }
        }
    }

    int si = K, sj = -1, sk = -1, sl = -1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= K; j++) {
            auto [x, y, z] = dp[K][0][i][j];
            if(x != -1) {
                sj = 0, sk = i, sl = j;
            }
        }
    }

    if(sj == -1) {
        vector<pair<string, vector<int>>> res;
        string first = string(K / 2, '(') + string(K / 2, ')');
        string second = "";
        for(int i = 0; i < K; i += 2) {
            second.append("()");
        }
        res.push_back({first, {}});
        res.push_back({second, {}});
        vector<int> vis(n);
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < n; j++) {
                if(vis[j] == 0 && res[i].first.find(a[j]) == string::npos) {
                    res[i].second.push_back(j);
                    vis[j] = 1;
                }
            }
        }
        if(count(vis.begin(), vis.end(), 0)) {
            cout << "-1\n";
        } else {
            cout << "2\n";
            for(int i = 0; i < 2; i++) {
                cout << res[i].first << '\n';
                cout << res[i].second.size() << '\n';
                for(int j = 0; j < res[i].second.size(); j++) {
                    cout << res[i].second[j] + 1 << " ";
                }
                cout << '\n';
            }
        }
    } else {
        string res = "";
        // cout << "i : " << si << " j : " << sj << " k : " << sk << " l : " << sl << endl;
        while(si) {
            auto [nj, nk, nl] = dp[si][sj][sk][sl];
            // cout << "si : " << si << " nj : " << nj << " nk : " << nk << " nl : " << nl << endl;
            if(nj < sj) {
                res.push_back('(');
            } else {
                res.push_back(')');
            }
            si--;
            sj = nj;
            sk = nk;
            sl = nl;
        }
        reverse(res.begin(), res.end());
        cout << "1\n" << res << '\n' << n << '\n';
        for(int i = 0; i < n; i++) cout << i + 1 << " \n"[i == n - 1];
    }

    return 0;
}
