#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int solve1(int r, int g, int b) {
    // if(b < g || ((b - g) & 1) || (r + g + b - b)) return -1;
    // return b;
    int ops = b;
    int g_ops = (b - g) / 3;
    int r_ops = ops - g_ops;
    // cout << "r : " << r << " g : " << g << " b : " << b << " ops : " << ops << " g_ops : " << g_ops << " r_ops : " << r_ops << '\n';
    if(g > b) return 1e9;
    if((b - g) % 3 != 0) return 1e9;
    if(r != (r + g + b) - r_ops * 2 + g_ops) return 1e9;
    if(g != r_ops - g_ops * 2) return 1e9;
    if(b != r_ops + g_ops) return 1e9;
    return ops;
}

void solve() {
    int r, g, b; cin >> r >> g >> b;
    int ans = min({solve1(r,g,b),
                 solve1(r,b,g),
                 solve1(b,g,r),
                 solve1(b,r,g),
                 solve1(g,r,b),
                 solve1(g,b,r)
    });
    cout << (ans == 1e9 ? -1 : ans) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}