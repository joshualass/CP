#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll solve(vector<ll> &v, int pos) {
    vector<ll> dp(6);
    int n = v.size();
    pos++; //1-index pos
    dp[0] = 1; //1 way to make of length 0
    for(int i = 0; i < n; i++) {
        if(v[i] & 1) {
            for(int j = (pos + 1) % 3 + 1; j % 3 != pos % 3; j--) {
                if(j == 0) {
                    j += 3;
                }

                if(j == 3) {
                    dp[3] += dp[2];
                    dp[3] += dp[5];
                } else if(j == 2) {
                    dp[2] += dp[1];
                    dp[5] += dp[4];
                } else if(j == 1) {
                    dp[1] += dp[0];
                    dp[4] += dp[3];
                }
            }
        } else {
            if(pos == 3) {
                dp[3] += dp[2];
                dp[3] += dp[5];
            } else if(pos == 2) {
                dp[2] += dp[1];
                dp[5] += dp[4];
            } else if(pos == 1) {
                dp[1] += dp[0];
                dp[4] += dp[3];
            }
            
        }
        for(int j = 0; j < 6; j++) {
            dp[j] %= MOD;
        }
        // cout << "i : " << i << " dp : " << dp << '\n';
    }
    // cout << "v : " << v << " dp : " << dp << " pos : " << pos << '\n';
    return dp[3] + dp[4] + dp[5];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;

    vector<ll> even_lengths(3);
    ll res = 0;

    for(int i = 0; i < n; i++) {
        if((v[i] & 1) == 0) {
            //for only evens
            even_lengths[2] += even_lengths[2];
            even_lengths[2] += even_lengths[1];
            even_lengths[1] += even_lengths[0];
            even_lengths[0]++;
            even_lengths[2] %= MOD;
            even_lengths[1] %= MOD;
            even_lengths[0] %= MOD;
        }
    }

    // cout << "evenlengths : " << even_lengths << '\n';
    res += even_lengths[2];
    res += solve(v, 0);
    res += solve(v, 1);
    res += solve(v, 2);

    cout << res % MOD << '\n';

    return 0;
}