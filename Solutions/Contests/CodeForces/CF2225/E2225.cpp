#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

int debug = 0;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r; 
    if(debug == 0) {
        cin >> n >> r;
    } else {
        n = 10000, r = 100;
    }
    set<array<int,2>> s;
    int cnt = 0;

    int o1 = r;
    int oy = 0;
    while(sqrt(o1 * o1 + oy * oy) - 0.0000001 <= r * 2) oy++;

    int p = oy * 2;

    for(int i = 0; i < n; i++) {
        int x, y; 
        if(debug == 0) {
            cin >> x >> y;
        } else {
            x = rng() % 600 - 300, y = rng() % 600 - 300;
        }

        int tx = 0, ty = 0;
        if(x < 0) {
            x *= -1;
            tx = 1;
        }
        if(y < 0) {
            y *= -1;
            ty = 1;
        }

        array<int,2> f = {inf, inf};

        {
            int tx = (x + r) / (r * 2) * (r * 2);
            int ty = (y + oy) / p * p;
            if((tx - x) * (tx - x) + (ty - y) * (ty - y) <= r * r) {
                f = {tx, ty};
            }
        }
        {
            int tx = x / (r * 2) * (r * 2) + r;
            int ty = y / p * p + oy;
            if((tx - x) * (tx - x) + (ty - y) * (ty - y) <= r * r) {
                f = {tx, ty};
            }
        }

        if(f != array<int,2>{inf, inf}) {
            if(tx) f[0] *= -1;
            if(ty) f[1] *= -1;
            s.insert(f);
            cnt++;
        }
    }

    // cout << "cnt : " << cnt << endl;

    assert(cnt >= (n * 89 + 99) / 100);

    cout << sz(s) << '\n';
    for(auto [x, y] : s) cout << x << " " << y << '\n';

    return 0;
}
