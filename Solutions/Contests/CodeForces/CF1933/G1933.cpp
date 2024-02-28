#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void rotate90(int &x, int &y, int n, int m) {
    swap(x,y);
    x = n - x - 1;
}

void offset(int &x, int &y) {
    x++;
}

bool getval(int x, int y) {
    return ((x & 2) >> 1) ^ (y & 1);
}

void solve() {
    int n, m, q; cin >> n >> m >> q;
    cout << "8\n";
    if(q == 0) return;
    cout << "4\n";
    vector<bool> vals(4);
    vector<int> ok(4,1);
    int y, x; cin >> y >> x;
    y--; x--;
    string s; cin >> s;
    for(int i = 0; i < 4; i++) {
        int tx = x, ty = y;
        if(i & 1) {
            rotate90(tx,ty,n,m);
        }
        if(i & 2) {
            offset(tx,ty);
        }
        vals[i] = (s == "circle") ^ getval(tx,ty);
    }
    for(int i = 0; i < q - 1; i++) {
        cin >> y >> x >> s;
        x--; y--;
        for(int j = 0; j < 4; j++) {
            int tx = x, ty = y;
            if(j & 1) {
                rotate90(tx,ty,n,m);
            }
            if(j & 2) {
                offset(tx,ty);
            }
            ok[j] &= ((s == "circle") ^ getval(tx,ty)) == vals[j];
        }
        cout << reduce(ok.begin(), ok.end()) << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}