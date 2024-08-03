#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
This problems uses some techniques that are pretty common for greedy techniques using bitwise operations.
First observe that starting from the most significant bit, every bit that is same in l and r is going to be present no matter which value is used.
After the bits differ which must happen when for a certain bit i, there is a 0 for l and a 1 for r, We now have a greedy option enabled now. 
This greedy option is that we can either choose to have a 1 set for the i'th bit or have the i'th bit set to 0 and all the bits following i set to 1. 
We can use this greedy option now for every set bit following i in r. 
By looking at forced bits and greedy option bits, we can pretty easily see a greedy solution after taking prefix sums of each of these bits to see how many of each option we have. 
*/

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> forced(n+1, vector<int>(30));
    vector<vector<int>> option(n+1, vector<int>(30));

    for(int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y;
        bool same = 1;
        for(int bit = 29; bit >= 0; bit--) {
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
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        int res = 0;
        bool setone = 0;
        for(int bit = 29; bit >= 0; bit--) {
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
        cout << res << " \n"[i == q - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}