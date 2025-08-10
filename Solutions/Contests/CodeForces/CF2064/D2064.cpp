#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int nearest[200000][30];

void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] ^ a[i];
        int msb = 31 - __builtin_clz(a[i]);
        for(int bit = 29; bit >= 0; bit--) {
            if(msb >= bit) {
                nearest[i][bit] = i;
            } else {
                nearest[i][bit] = (i ? nearest[i-1][bit] : -1);
            }
        }
    }

    for(int qq = 0; qq < q; qq++) {
        int x; cin >> x;
        int cur = n - 1;
        // cout << "qq : " << qq << " x : " << x << " cur : " << cur << '\n';
        while(cur != -1) {
            // cout << "x : " << x << " cur : " << cur << '\n';
            int msb = 31 - __builtin_clz(x);
            int nx_block = nearest[cur][msb];
            if(nx_block == -1) {
                cur = -1;
                break;
            }
            // cout << "msb : " << msb << " nx_block : " << nx_block << '\n';
            x ^= p[cur+1] ^ p[nx_block + 1];
            cur = nx_block;
            
            // cout << "after xor : " << x << '\n';
            if(x >= a[nx_block]) {
                x ^= a[nx_block];
                cur--;
                if(!x) break;
            } else {
                break;
            }
        }
        cout << n - cur - 1 << " \n"[qq == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}