#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()



void solve() {
    
    int n; cin >> n;

    n = n * 2 + 1;
    
    vector<int> f;
    int l = 1, r = n;

    //ask and return 1 if all 3 are present among these idxs
    auto ask = [&](vector<int> idxs) -> int {
        cout << "? " << sz(idxs);
        for(int x : idxs) cout << " " << x;
        cout << endl;
        int res; cin >> res;
        return (sz(idxs) - res) & 1;
    };

    while(sz(f) < 3) {
        int tl = l + 1, tr = n + 1;
        
        while(tl != tr) {
            int mid = (tl + tr) / 2;
            vector<int> idxs;
            for(int x : f) idxs.push_back(x);
            for(int i = mid; i <= r; i++) {
                idxs.push_back(i);
            }

            // cout << "tl : " << tl << " tr : " << tr << " mid : " << mid << endl;

            if(ask(idxs) == 0) {
                //the third element is not present
                tr = mid;
            } else {
                tl = mid + 1;
            }
        }
        
        // cout << "add f : " << tl - 1 << endl;

        f.push_back(tl - 1);
        l = tl;
    }

    cout << "! " << f[0] << " " << f[1] << " " << f[2] << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}