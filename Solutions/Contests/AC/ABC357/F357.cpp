#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const int MAXN = 2e5;
const int sqn = 447;

ll blockprods[sqn+1];
ll blockasums[sqn+1];
ll blockbsums[sqn+1];
ll blockadiffs[sqn+1];
ll blockbdiffs[sqn+1];

ll a[MAXN];
ll b[MAXN];

int getblock(int b) {
    return b / sqn;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(blockprods, 0, sizeof(blockprods));
    memset(blockasums, 0, sizeof(blockasums));
    memset(blockbsums, 0, sizeof(blockbsums));
    memset(blockadiffs, 0, sizeof(blockadiffs));
    memset(blockbdiffs, 0, sizeof(blockbdiffs));

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    for(int i = 0; i < n; i++) {
        blockasums[getblock(i)] += a[i];
        blockasums[getblock(i)] %= MOD;
        blockbsums[getblock(i)] += b[i];
        blockbsums[getblock(i)] %= MOD;
        blockprods[getblock(i)] += a[i] * b[i];
        blockprods[getblock(i)] %= MOD;
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll l, r, x; cin >> l >> r >> x;
            l--; r--;
            while(l <= r && l % sqn != 0) { //increase l until it is at the beginning of a block or it passes r
                int block = getblock(l);
                //remove current product
                blockprods[block] -= (a[l] + blockasums[block]) * (b[l] * blockbsums[block]) % MOD;
                if(blockprods[block] < 0) blockprods[block] += MOD;
                //update a stuff
                a[l] += x;
                a[l] %= MOD;
                blockasums[block] += x;
                blockasums[block] %= MOD;
                //update current product
                blockprods[block] += (a[l] + blockasums[block]) * (b[l] * blockbsums[block]) % MOD;
                blockprods[block] %= MOD;
                l++;
            }
        }
    }

    return 0;
}