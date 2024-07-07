#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//found nice pattern for Wilson's theorem

const int N = 15;
ll factorials[N+1];
ll pc[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i;
    }
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return factorials[n] / factorials[n-k] / factorials[k];
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();

    ll stop = 15;
    for(ll j = 1; j <= stop; j++) {
        for(ll i = j; i <= stop; i++) {
            ll v = choose(i,j) * factorials[j - 1];
            cout << "i : " << i << " j : " << j << " v : " << v << " res : " << v % j << '\n';
        }
        cout << "--------------------------------\n";
    }

    // for(ll i = 1; i <= 100; i++) {
    //     ll res = 1;
    //     for(ll j = 1; j < i; j++) {
    //         res = res * j % i;
    //     }
    //     cout << "i : " << i << " res % i : " << res % i << '\n';
    // }

    return 0;
}