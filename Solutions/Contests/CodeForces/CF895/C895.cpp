#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

bool isPrime(int n) {
    if(n <= 1) {
        return false;
    }
    if(n == 2 || n == 3) {
        return true;
    }
    if(n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for(int i = 5; i <= sqrt(n); i+= 6) {
        if(n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int dp[1 << 11], nextdp[1 << 11];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> primes;
    for(int i = 0; i <= 35; i++) {
        if(isPrime(i)) {
            primes.push_back(i);
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int n; cin >> n;
    array<int, 70> remainders{};
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        int bm = 0;
        for(int j = 0; j < primes.size(); j++) {
            while(num % primes[j] == 0) {
                bm ^= 1 << j;
                num /= primes[j];
            }
        }
        if(num != 1) {
            remainders[num]++;
        } else {
            if(bm) {
                for(int i = 0; i < 1 << 11; i++) {
                    nextdp[i ^ bm] = (dp[i] + dp[i ^ bm]) % MOD;
                }
                swap(nextdp, dp);
            } else {
                remainders[1]++;
            }
        }
    }

    ll res = (dp[0] * binexp(2, remainders[1])) % MOD;
    for(int i = 2; i < 70; i++) {
        if(remainders[i]) {
            res = (res * binexp(2, remainders[i] - 1)) % MOD;
        }
    }

    cout << (res + MOD - 1) % MOD << '\n';

    return 0;
}