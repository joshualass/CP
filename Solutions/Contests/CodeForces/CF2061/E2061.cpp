#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    vector<vector<int>> op_ands(1 << m);

    for(int i = 0; i < 1 << m; i++) {
        int res = INT_MAX;
        for(int j = 0; j < m; j++) {
            if((i >> j) & 1) {
                res &= b[j];
            }
        }
        op_ands[__builtin_popcount(i)].push_back(res);
    }

    // cout << "op_ands : " << op_ands << '\n';

    auto find_max_diff = [&](int idx) -> vector<int> {
        vector<int> res(m+1);
        for(int i = 0; i <= m; i++) {
            int r = a[idx];
            for(int x : op_ands[i]) {
                r = min(r, a[idx] & x);
            }
            res[i] = r;
        }
        return res;
    };

    vector<vector<int>> best_ops(n);
    priority_queue<array<int,2>> pq;
    vector<int> states(n);

    auto add_queue = [&](int idx) -> void {
        int state = states[idx];
        if(state + 1 <= m) {
            pq.push({best_ops[idx][state] - best_ops[idx][state + 1], idx});
            states[idx]++;
        }
    };

    for(int i = 0; i < n; i++) {
        best_ops[i] = find_max_diff(i);
        // cout << "i : " << i << " best_ops[i] : " << best_ops[i] << '\n';
        add_queue(i);
    }

    while(k && pq.size()) {
        k--;
        auto [diff, idx] = pq.top();
        pq.pop();
        a[idx] -= diff;
        add_queue(idx);
    }

    cout << accumulate(a.begin(), a.end(), 0LL) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}