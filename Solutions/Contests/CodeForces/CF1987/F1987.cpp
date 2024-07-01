#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*

6
1 2 1 10 10 10

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;    
    }

    vector<vector<bool>> poss(n, vector<bool>(n));
    vector<int> dp(n);

    for(int hi = 1; hi < n; hi++) {
        for(int lo = hi - 1; lo >= 0; lo--) {
            for(int i = lo + 1; i + 1 < hi; i++) {
                poss[lo][hi] = poss[lo][hi] || (poss[lo][i] && poss[i+1][hi]);
            }
            bool hit = 0;
            int mb = lo == 0 ? lo : dp[lo-1];
            for(int i = 0; i <= mb; i += 2) {
                if(a[lo] == lo - i) hit = 1;
            }
            if(hit && (poss[lo+1][hi-1] || hi - lo == 1)) {
                poss[lo][hi] = 1;
            }
            if(poss[lo][hi]) {
                cout << "poss : " << lo << ", " << hi << '\n';
                for(int i = hi; i < n; i++) {
                    dp[i] = max(dp[i], mb + hi - lo + 1);
                }
            }
        }
    }



    cout << "poss\n" << poss;

    cout << (*max_element(dp.begin(), dp.end()) >> 1) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}