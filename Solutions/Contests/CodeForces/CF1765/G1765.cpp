#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n; cin >> n;

    auto ask = [&](int type, int i) -> int {
        cout << type << " " << i + 1 << endl;
        int res; cin >> res;
        return res;
    };

    vector<int> res(1, 0);

    auto fn = [&](int type, int val) -> void {
        int x;
        if(val == 0) {
            if(type == 1) {
                x = 1;
            } else {
                x = 0;
            }
        } else {
            if(type == 1) {
                x = res[val - 1];
            } else {
                x = 1 ^ res[val - 1];
            }
        }
        res.push_back(x);
    };

    auto sn = [&]() -> void {
        int val = ask(1, sz(res));
        fn(1, val);
    };

    sn();

    while(sz(res) + 2 <= n) {
        int type = (rng() & 1)+ 1;
        int nx = sz(res) + 1;
        int val = ask(type, nx);
        // cout << "type gg : " << type << endl;
        if(val >= 2) {
            fn(type, val - 1);
            fn(type, val);
        } else {
            vector<vector<int>> cands;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    vector<int> cur = {i, j};
                    auto act = cur;
                    if(type == 2) {
                        for(int &x : act) x ^= 1;
                    }
                    int match = 0;
                    for(int test = 1; test <= 2; test++) {
                        int ok = 1;
                        for(int k = 0; k < test; k++) {
                            if(act[2 - test + k] != res[k]) ok = 0;
                        }
                        if(ok) match = test;
                    }
                    // cout << "cur : " << cur << " match : " << match << endl;
                    if(match == val) cands.push_back(cur);
                }
            }
            assert(sz(cands));
            if(sz(cands) == 1) {
                auto cand = cands[0];
                // cout << "cand : " << cand << endl;
                res.push_back(cand[0]);
                res.push_back(cand[1]);
            } else {
                sn();
                fn(type, val);
            }
        }
    }

    if(sz(res) != n) sn();

    cout << "0 ";
    for(int x : res) cout << x;
    cout << endl;

    int ok; cin >> ok;
    if(ok == -1) assert(0);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}