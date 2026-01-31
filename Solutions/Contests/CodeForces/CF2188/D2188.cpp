#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// int solve(int x, int y) {
int solve() {
    int x, y; cin >> x >> y;



    //finds closest to y
    auto solve_other = [&](int p, int y) -> int {

        auto dfs = [](auto self, int p, int y, int bit, int cur) -> int {
            // cout << "x : " << x << " y : " << y << " bit : " << bit << " cur : " << cur << endl;
            //base case 
            if(bit == -1) {
                return cur;
            }
            //no choice 
            if((p >> bit) & 1) {
                return self(self, p, y, bit - 1, cur);
            }

            int rem = (1 << bit) - 1;
            if(rem >= y - cur) {
                //try both, single pivot
                int test = self(self, p, y, bit - 1, cur);
                if(test >= y) return test;
            }
            return cur + (1 << bit);
        };

        int dfs_over = dfs(dfs, p, y, 30, 0);
        int cur = 0;
        for(int bit = 30; bit >= 0; bit--) {
            if(((p >> bit) & 1) == 0 && cur + (1 << bit) <= y) {
                cur += 1 << bit;
            }
        }

        if(abs(dfs_over - y) < abs(cur - y)) {
            return dfs_over;
        } else {
            return cur;
        }
    };

    array<int,2> soln = {};
    int cs = x + y;

    auto add_soln = [&](int p, int q) -> void {
        int test = abs(x-p) + abs(y - q);
        if(test < cs) {
            cs = test;
            soln = {p, q};
        }
    };

    int cur = 0;
    for(int bit = 30; bit >= 0; bit--) {
        if(((x >> bit) & 1) == 0) {
            add_soln(cur + (1 << bit), solve_other(cur + (1 << bit), y));
        } else {
            cur += 1 << bit;
        }
    }

    add_soln(cur, solve_other(cur, y));

    cur = 0;
    for(int bit = 30; bit >= 0; bit--) {
        if(((y >> bit) & 1) == 0) {
            add_soln(solve_other(cur + (1 << bit), x), cur + (1 << bit));
        } else {
            cur += 1 << bit;
        }
    }

    add_soln(solve_other(cur, x), cur);

    cout << soln[0] << " " << soln[1] << '\n';

    return cs;

}

int solve_slow(int x, int y) {
    array<int,2> res = {};
    int cur = x + y;
    for(int p = 0; p <= x * 2; p++) {
        for(int q = 0; q <= y * 2; q++) {
            if((p & q) == 0) {
                int test = abs(x - p) + abs(y - q);
                if(test < cur) {
                    res = {p, q};
                    cur = test;
                }
            }
        }
    }
    return cur;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 0; i < 30; i++) {
    //     for(int j = 0; j < 30; j++) {
    //         if(solve(i, j) != solve_slow(i, j)) {
    //             cout << "i : " << i << " j : " << j << endl;
    //             int s = solve(i, j), ss = solve_slow(i, j);
    //             cout << "s : " << s << " ss : " << ss << endl;
    //             return 0;
    //         }
    //     }
    // }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}