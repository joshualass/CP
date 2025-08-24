#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
bitset<2001> bs{};

/*


*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, d; cin >> n >> d;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> dp(d + 1, -1);
    dp[0] = -2;

    for(int i = 0; i < n; i++) {
        for(int j = d - a[i]; j >= 0; j--) {
            if(dp[j] != -1 && dp[j + a[i]] == -1) {
                dp[j + a[i]] = i;
            }
        }
    }

    // cout << "dp : " << dp << '\n';

    int f = 0;
    
    for(int bl = 0, bh = d; bl <= bh; bl++, bh--) {
        // cout << "bl : " << bl << " bh : " << bh << endl;
        if(dp[bl] != -1) {
            vector<int> used(n);
            int cur = bl;
            while(cur) {
                // cout << "cur : " << cur << endl;
                assert(used[dp[cur]] == 0);
                used[dp[cur]] = 1;
                cur -= a[dp[cur]];
            }
            bs.reset();
            bs[0] = 1;
            int targ = d - bl;
            for(int j = 0; j < n; j++) {
                if(used[j] == 0) {
                    if(a[j] > bl) {
                        targ -= a[j];
                    } else {
                        bs |= bs << a[j];
                    }
                }
            }
            // cout << "bl : " << bl << " targ : " << targ << " bs : " << bs << '\n';
            if(targ >= 0 && bs[targ]) f = 1;
        }
    }


    cout << (f ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}