#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<int> a(n), b(n); //a[i] / b[i]
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) {
        cin >> x;
        x--;
    }
    vector<int> ra(n), rb(n); //index i stores the index in a of value i
    for(int i = 0; i < n; i++) {
        ra[a[i]] = i;
        rb[b[i]] = i;
    }

    int invs = 0;

    auto add_inv = [&](int i, int delta) {
        // cout << "inv work i : " << i << endl;
        int c = ra[b[i-1]], d = ra[b[i]];
        if(c > d) invs += delta;
    };

    for(int i = 1; i < n; i++) {
        add_inv(i, 1);
    }

    auto print_res = [&]() -> void {
        int last_idx = ra[b[n-1]];
        // cout << "invs : " << invs << " last : " << last_idx << '\n';
        cout << 1LL * (invs - 1) * (n) + last_idx + 1 << '\n';
    };

    print_res();

    for(int qq = 0; qq < d - 1; qq++) {
        int c, x, y; cin >> c >> x >> y;
        x--; y--;
        set<int> s;
        if(c == 1) {
            int xval = a[x], yval = a[y];
            s.insert(rb[xval]);
            s.insert(rb[xval] + 1);
            s.insert(rb[yval]);
            s.insert(rb[yval] + 1);
        }
        if(c == 2) {
            s.insert(x);
            s.insert(x + 1);
            s.insert(y);
            s.insert(y + 1);
        }

        s.erase(0);
        s.erase(n);

        for(int x : s) add_inv(x, -1);

        if(c == 1) {
            swap(a[x], a[y]);
            swap(ra[a[x]], ra[a[y]]);
            assert(x == ra[a[x]]);
            assert(y == ra[a[y]]);
        }
        if(c == 2) {
            swap(b[x], b[y]);
            swap(rb[b[x]], rb[b[y]]);
            assert(x == rb[b[x]]);
            assert(y == rb[b[y]]);
        }

        for(int x : s) add_inv(x, 1);
        print_res();
    }

    return 0;
}
