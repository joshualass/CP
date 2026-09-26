#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int testing = 0;
ll solve_slow(int l, int r) {

    deque<int> left, right;
    for(int i = 0; i < l; i++) left.push_back(i);
    for(int i = 0; i < r; i++) right.push_back(i + l);

    set<array<int,2>> pairings;
    for(int i = 0; i < l * r * 20; i++) {
        int a = left.back(), b = right.front();
        if(a > b) swap(a,b);
        pairings.insert({a, b});
        if(i % 2 == 0) {
            int x = left.back();
            left.pop_back();
            right.push_back(x);
        } else {
            int x = right.front();
            right.pop_front();
            left.push_front(x);
        }
    }

    return sz(pairings);

}

ll solve(int l, int r) {

    auto get = [](int l, int r) -> ll {
        set<int> vis;
        vis.insert(l);
        vis.insert(l - 1);
        vis.insert(r);
        vis.insert(r + 1);
        // assert()
        return sz(vis);
    };

    if((l + r) % 2 == 0) {
        return ((l + r) / 2 * (get(l, r) + get(r + 1, l - 1))) / 2;
    } else {
        return ((l + r) * get(l, r)) / 2;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(testing) {

        for(int l = 2; l <= 10; l++) {
            for(int r = 1; r <= 10; r++) {
                ll res_fast = solve(l, r);
                ll res_slow = solve_slow(l, r);
                if(res_fast != res_slow) {
                    cout << "l : " << l << " r : " << r << " fast : " << res_fast << " slow : " << res_slow << endl;
                    return 0;
                }
            }
        }
        cout << "ok!" << endl;
    } else {
        int l, r; cin >> l >> r;
        cout << solve(l, r) << '\n';
    }


    return 0;
}
