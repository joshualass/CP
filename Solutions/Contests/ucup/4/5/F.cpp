#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int dsu[1 << 12][1000];

void dsubuild(int n) {
    for(int i = 0; i < 1 << 12; i++) {
        for(int j = 0; j < n; j++) {
            dsu[i][j] = j;
        }
    }
}

int find(int x, int mask) {
    if(x != dsu[mask][x]) {
        dsu[mask][x] = find(dsu[mask][x], mask);
    }
    return dsu[mask][x];
}

void merge(int x, int y, int mask) {
    int nx = find(x, mask), ny = find(y, mask);
    if(nx == ny) return;
    dsu[mask][ny] = nx;
    for(int i = 0; i < 12; i++) {
        if((mask >> i) & 1) {
            merge(x, y, mask ^ (1 << i));
        }
    }
}

void solve() {
    
    int n, q; cin >> n >> q;

    dsubuild(n);
    ll tot = 0;

    for(int qq = 0; qq < q; qq++) {
        char type; cin >> type;
        // cout << "qq : " << qq << endl;
        if(type == '+') {
            int u, v, w; cin >> u >> v >> w;
            u--; v--;
            merge(u, v, w);
        } else {
            int u, v; cin >> u >> v;
            u--; v--;
            int res = 0;
            for(int i = 11; i >= 0; i--) {
                int test = res + (1 << i);
                if(find(u, test) == find(v, test)) {
                    res += 1 << i;
                }
            }
            // cout << "res : " << res << endl;
            if(res == 0 && find(u, 0) != find(v, 0)) res--;
            tot += res;
        }
    }

    cout << tot << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}