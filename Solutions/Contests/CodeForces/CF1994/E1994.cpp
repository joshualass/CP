#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//bruh ---- https://codeforces.com/contest/1935/submission/270076307
int forced[1000001][22];
int option[1000001][22];

void solve() {
    int k; cin >> k;
    vector<int> a(k);

    for(int i = 0; i < k; i++) {
        cin >> a[i];
        for(int j = 1; j < a[i]; j++) {
            int trash; cin >> trash;
        }
        int x = 1, y = a[i];
        bool same = 1;
        i++;
        for(int bit = 21; bit >= 0; bit--) {
            forced[i][bit] = forced[i-1][bit];
            option[i][bit] = option[i-1][bit];
            if(((x >> bit) & 1) == ((y >> bit) & 1) && same) {
                if((x >> bit) & 1) {
                    forced[i][bit]++;
                }
            } else {
                same = 0;
                if((y >> bit) & 1) {
                    option[i][bit]++;
                }
            }
        }
        i--;
    }

    int l = 0, r = k;
    int res = 0;
    bool setone = 0;
    for(int bit = 21; bit >= 0; bit--) {
        if(setone) {
            res |= 1 << bit;
        }
        int force = forced[r][bit] - forced[l][bit];
        int options = option[r][bit] - option[l][bit];
        if(force || options) {
            res |= 1 << bit;
        }
        if(options && (force + options >= 2)) {
            setone = 1;
        }
    }
    cout << res << "\n";


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}