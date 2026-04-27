#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}
#define sz(x) (int) (x).size()

const int mx = 8 * 100'000 + 1; 

vector<bitset<mx>> dp(8);
bitset<mx> bad {};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i * i < mx; i++) {
        bad[i * i] = 1;
    }

    dp[0][0] = 1;

    vector<int> res;

    for(int i = 100000; i >= 1; i--) {
        int ok = 1;
        for(int j = 0; j < 8; j++) {
            if(((bad >> i) & dp[j]).count()) ok = 0;
        }
        if(ok) {
            for(int j = 6; j >= 0; j--) {
                dp[j+1] |= (dp[j] << i);
            }
            res.push_back(i);
        } else {
            // cout << "bad detected : " << i << endl;
        }
    }

    cout << "size : " << sz(res) << endl;
    cout << res << endl;

    return 0;
}
