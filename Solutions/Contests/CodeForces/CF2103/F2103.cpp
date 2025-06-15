#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// vector<int> solve(int n, int k, vector<int> a) {
void solve() {
    
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> b(n, vector<int>(k));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            if((a[i] >> j) & 1) {
                b[i][j] = i;
            } else {
                b[i][j] = (i ? b[i-1][j] : -1);
            }
        }
    }

    auto get_bit = [&](int l, int r, int one) -> int {
        if(l == one) l++;
        if(one > l) l = one;
        if((r - l) & 1) { //even length, 1
            return 1;
        } else { //odd length, 0
            return 0;
        }
    };

    int id = 0;
    vector<vector<array<int,2>>> c(n + 1), d(n + 1);

    auto add_range = [&](int l, int r) -> void {
        if(l >= 0 && l <= r && r < n) {
            int res = 0;
            for(int i = 0; i < k; i++) {
                res += get_bit(l, r, b[r][i]) << i;
            }
            c[l].push_back({res, id});
            d[r+1].push_back({res, id++});
        }
    };

    for(int i = 0; i < n; i++) {
        add_range(0, i);
        add_range(1, i);
        add_range(i, i);
        for(int j = 0; j < k; j++) {
            add_range(b[i][j], i);
            add_range(b[i][j] + 1, i);
            add_range(b[i][j] + 2, i);
        }
    }

    priority_queue<array<int,2>> pq;
    vector<int> active(id);
    // vector<int> res;
    for(int i = 0; i < n; i++) {
        for(auto [res, idx] : c[i]) {
            active[idx] = 1;
            pq.push({res, idx});
        }
        for(auto [res, idx] : d[i]) {
            active[idx] = 0;
        }
        while(pq.size() && active[pq.top()[1]] == 0) pq.pop();
        cout << pq.top()[0] << " \n"[i == n - 1];
        // res.push_back(pq.top()[0]);
    }

    // return res;

}

vector<int> solve_slow(int n, int k, vector<int> a) {
    vector<int> res(n);
    auto get_nor = [&](int l, int r) -> int {
        int res = 0;
        for(int i = 0; i < k; i++) {
            if(((l >> i) & 1) == 0 && ((r >> i) & 1) == 0) {
                res += 1 << i;
            }
        }
        return res;
    };

    for(int l = 0; l < n; l++) {
        for(int r = l; r < n; r++) {
            int nor = a[l];
            for(int i = l + 1; i <= r; i++) nor = get_nor(nor, a[i]);
            // cout << "l : " << l << " r : " << r << " nor : " << nor << '\n';
            for(int i = l; i <= r; i++) res[i] = max(res[i], nor);
        }
    }
    return res;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int tc, n, k; cin >> tc >> n >> k;
    // for(int i = 0; i < tc; i++) {
    //     vector<int> a(n);
    //     for(int j = 0; j < n; j++) {
    //         a[j] = rng() & ((1 << k) - 1);
    //     }
    //     vector<int> res_fast = solve(n, k, a);
    //     vector<int> res_slow = solve_slow(n, k, a);
    //     if(res_fast != res_slow) {
    //         cout << "a : " << a << '\n';
    //         cout << "res fast : " << res_fast << '\n';
    //         cout << "res slow : " << res_slow << '\n';
    //         return 0;
    //     }
    // }

    // int n = 5, k = 2;
    // vector<int> a = {3, 3, 3, 2, 0};

    // vector<int> res_fast = solve_slow(n, k, a);
    // cout << "fast : " << res_fast << '\n';


    // cout << "ALL OK!\n";

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}