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

vector<array<int,3>> temp(4000000);

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

struct Tree {
    //{r, v, c}
    vector<vector<array<int,3>>> v;
    int n, size;
    Tree(int n) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void update(array<int,3> info, int l, int r) {
        // cout << "add info : " << info << " to range l : " << l << " r : " << r << '\n';
        _update(1, 0, size, l, r, info);
    }
    void _update(int idx, int curl, int curr, int tl, int tr, array<int,3> &info) {
        if(curr <= tl || curl >= tr) return;
        if(curl >= tl && curr <= tr) {
            // cout << "overlap append : " << curl << ", " << curr << '\n';
            v[idx].push_back(info);
            return;
        }
        int mid = (curl + curr) / 2;
        _update(idx * 2, curl, mid, tl, tr, info);
        _update(idx * 2 + 1, mid, curr, tl, tr, info);
    }
    void queries(vector<array<int,3>> &q, vector<array<ll,2>> &res, vector<int> &q_idx) {
        _queries(1, 0, size, q, res, q_idx);
    }
    void _queries(int idx, int curl, int curr, vector<array<int,3>> &q, vector<array<ll,2>> &res, vector<int> &q_idx) {
        if(v[idx].size()) {
            int qs = q_idx[curl], qe = q_idx[curr];
            int sz = qe - qs;
            for(int i = qs; i < qe; i++) {
                temp[i - qs] = {q[i][1], INT_MAX, q[i][2]};
            }
            for(int i = 0; i < v[idx].size(); i++) {
                temp[i + sz] = v[idx][i];
            }
            sz += v[idx].size();
            sort(temp.begin(), temp.begin() + sz);
    
            ll cur_v = 0, cur_c = 0;
            for(int i = 0; i < sz; i++) {
                if(temp[i][1] == INT_MAX) {
                    int id = temp[i][2];
                    res[id][0] += cur_v;
                    res[id][1] += cur_c;
                } else {
                    cur_v += temp[i][1];
                    cur_c += temp[i][2];
                }
            }
            // cout << "queries idx : " << idx << " curl : " << curl << " curr : " << curr << " cur_v : " << cur_v << " cur_c : " << cur_c << '\n';
        }
        if(curl + 1 == curr) return;
        int mid = (curl + curr) / 2;
        _queries(idx * 2, curl, mid, q, res, q_idx);
        _queries(idx * 2 + 1, mid, curr, q, res, q_idx);
    }

};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> p(n);
    for(int &x : p) cin >> x;
    vector<array<int,3>> qs(q);
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        qs[i] = {l, r, i};
    }

    vector<array<ll,2>> res(q);

    auto solve = [&]() -> void {
        Tree tree(n);
        // {value, idx}
        stack<array<int,2>> st;
        st.push({n * 2, -1});

        for(int i = 0; i < n; i++) {
            int val = p[i];
            while(val > st.top()[0]) st.pop();
            int l = st.top()[1];
            // if(i == 3) {
                // cout << "i : " << i << " l : " << l << '\n';
                tree.update({i + 1, i - l - 1, 0}, 0, l + 1);
                tree.update({i + 1, i, 1}, l + 1, i);
            // }
            st.push({val, i});
        }

        sort(qs.begin(), qs.end());
        vector<int> q_idx(n + 1, q);

        for(int i = 0; i < q; i++) {
            q_idx[qs[i][0]] = min(q_idx[qs[i][0]], i);
        }

        for(int i = n - 1; i >= 0; i--) {
            q_idx[i] = min(q_idx[i], q_idx[i + 1]);
        }

        tree.queries(qs, res, q_idx);
        
        
        sort(qs.begin(), qs.end(), [](const auto &lhs, const auto &rhs) -> bool {
            return lhs[2] < rhs[2];
        });
        
        // cout << "qs : " << qs << '\n';
        // cout << "res : " << res << '\n';
        // cout << "q_idx : " << q_idx << '\n';

        for(int i = 0; i < q; i++) {
            res[i][0] -= res[i][1] * qs[i][0];
            res[i][1] = 0;
        }

        // cout << "final res after solve : " << res << '\n';

    };

    auto rev = [&]() -> void {
        reverse(p.begin(), p.end());
        for(int i = 0; i < q; i++) {
            swap(qs[i][0], qs[i][1]);
            for(int j = 0; j < 2; j++) {
                qs[i][j] = n - qs[i][j];
            }
        }
    };

    solve();
    rev();
    solve();

    for(int i = 0; i < q; i++) {
        cout << res[i][0] << '\n';
    }

    return 0;
}
