#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m, q; cin >> n >> m >> q;

    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; cin >> c;
            a[i][j] = c - '0';
        }
    }

    vector<int> b(n); //current toggles
    vector<int> c(1 << n); //current scores 

    auto get = [&](int i) -> int {
        int res = 0;
        for(int j = 0; j < n; j++) {
            res += (a[j][i] ^ b[j]) << j;
        }
        return res;
    };

    auto mindist = [&](int rt, int bm) -> int {
        bm ^= rt;
        int pc = __builtin_popcount(bm);
        return min(pc, 1 + (n - pc));
    };

    auto update = [&](int i, int d) -> void {
        int bm = get(i);
        for(int j = 0; j < 1 << n; j++) {
            c[j] += d * mindist(j, bm);
        }
    };

    auto add = [&](int i) -> void {
        update(i, 1);
    };

    auto sub = [&](int i) -> void {
        update(i, -1);
    };

    auto get_ans = [&]() -> int {
        int cur = 0;
        // for(int i = 0; i < n; i++) cur += b[i] << i;

        int minops = INT_MAX;
        for(int i = 0; i < 1 << n; i++) {
            minops = min(minops, __builtin_popcount(cur ^ i) + c[i]);
        }
        return minops;
    };

    for(int i = 0; i < m; i++) add(i);

    cout << get_ans() << '\n';

    auto prt = [&]() -> void {
        for(int i = 0; i < n; i++) {
            cout << "b[i] : " << b[i] << '\n';
        }
        for(int i = 0; i < 1 << n; i++) {
            cout << "bm : " << i << " cost : " << c[i] << '\n';
        }
    };

    // prt();

    for(int i = 0; i < q; i++) {
        char t; cin >> t;
        if(t == 'P') {
            int r, c; cin >> r >> c;
            r--; c--;
            sub(c);
            a[r][c] ^= 1;
            add(c);
        } else if(t == 'R') {
            int r; cin >> r;
            r--;
            for(int j = 0; j < 1 << n; j++) if((j >> r) & 1) swap(c[j], c[j ^ (1 << r)]);
            b[r] ^= 1;
        } else {
            int c; cin >> c;
            c--;
            sub(c);
            for(int j = 0; j < n; j++) a[j][c] ^= 1;
            add(c);
        }
        // cout << "i : " << i << '\n';
        // prt();
        cout << get_ans() << '\n';
    }

    return 0;
}