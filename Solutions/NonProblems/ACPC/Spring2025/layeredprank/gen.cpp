#include "testlib.h"
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(int args_length, char* args[]) {

    registerGen(args_length, args, 1);
    
    int n = stoi(args[1]);
    int m = stoi(args[2]);
    int k = stoi(args[3]);
    int all_rand = stoi(args[4]);

    auto get_rand = [&](int lo, int hi) -> int {
        return (((int) rnd.next(LLONG_MAX)) % (hi - lo + 1) + (hi - lo + 1) ) % (hi - lo + 1) + lo;
    };

    auto get_rand_pt = [&](array<int,2> a, int var) -> array<int,2> {

        array<int,2> lo = {max(0, a[0] - var), max(0, a[1] - var)};
        array<int,2> hi = {min(n, a[0] + var), min(m, a[1] + var)};

        return array<int,2>{get_rand(lo[0], hi[0]), get_rand(lo[1], hi[1])};

    };

    auto fix_pt = [](array<int,2> &a, array<int,2> &b) -> bool {
        if(a[0] == b[0] || a[1] == b[1]) return 0;
        if(a[0] > b[0]) swap(a[0], b[0]);
        if(a[1] > b[1]) swap(a[1], b[1]);
        return 1;
    };

    vector<array<array<int,2>, 2>> res;

    if(all_rand) {

        for(int i = 0; i < k; i++) {
            array<int,2> a, b;
            while(1) {
                a = get_rand_pt({0,0}, max(n,m));
                b = get_rand_pt({0,0}, max(n,m));
                if(fix_pt(a,b)) {
                    break;
                }
            }
            res.push_back({a, b});
        }

    } else {
        int lat_dim = stoi(args[5]);
        int var = stoi(args[6]);
        assert(lat_dim > 1 && lat_dim <= min(n, m) + 1);

        set<int> xs, ys;
        for(int i = 0; i < lat_dim; i++) {
            while(1) {
                int xp = rnd.next(LLONG_MAX) % (n + 1);
                if(xs.count(xp) == 0) {
                    xs.insert(xp);
                    break;
                }
            }
            while(1) {
                int yp = rnd.next(LLONG_MAX) % (m + 1);
                if(ys.count(yp) == 0) {
                    ys.insert(yp);
                    break;
                }
            }
        }

        vector<int> x(xs.begin(), xs.end()), y(ys.begin(), ys.end());

        for(int i = 0; i < k; i++) {
            array<int,2> a, b;
            while(1) {
                a = get_rand_pt({x[get_rand(0, x.size() - 1)], y[get_rand(0, y.size() - 1)]}, var);
                b = get_rand_pt({x[get_rand(0, x.size() - 1)], y[get_rand(0, y.size() - 1)]}, var);
                if(fix_pt(a,b)) {
                    break;
                }
            }
            res.push_back({a,b});
        }

    }

    cout << n << " " << m << " " << k << '\n';
    for(array<array<int,2>, 2> x : res) {
        cout << x[0][0] << " " << x[0][1] << " " << x[1][0] << " " << x[1][1] << '\n';
    }

    return 0;
}
