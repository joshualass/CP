#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k; cin >> k;
    vector<int> a(1 << k);
    vector<int> vis(1 << k);
    
    for(int i = 0; i < 1 << k; i++) {
        cin >> a[i];
        if(a[i] != -1) {
            vis[i] = 1;
        }
    }

    ll res = 1;

    for(int d = k; d > 0; d--) {

        int cnt = 0;
        int blocksize = 1 << (k - d + 1);
        int blockcnt = 1 << (d - 1);

        // cout << "d : " << d << " blocksize : " << blocksize << " blockcnt : " << blockcnt << '\n';

        for(int block = 0; block < blockcnt; block++) {
            int blockvis = 0;
            int dblockcnt = 0;
            for(int i = 0; i < blocksize; i++) {
                blockvis += vis[block * blocksize + i];
                if(a[block * blocksize + i] >= (1 << (d - 1)) + 1 && a[block * blocksize + i] <= 1 << d) {
                    dblockcnt++;
                } 
            }

            // cout << "block : " << block << " dblockcnt : " << dblockcnt << '\n';


            if(dblockcnt >= 2) {
                res = 0;
            }
            if(dblockcnt == 0) {
                cnt++;
                res = (res * cnt) % MOD;
                res = (res * (blocksize - blockvis)) % MOD;
                vis[block * blocksize]++;
            }
        }

    }

    cout << res << '\n';

    return 0;
}