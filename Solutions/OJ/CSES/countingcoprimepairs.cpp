#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MAXN = 1e6 + 1;
ll cnts[MAXN];
ll a[MAXN];

/*
Interesting solution, but I don't know where this falls under as math goes.
To me, I tried to use the principles of inclusion/exclusion. Because at heart, we can just look at all the primes and count the number of pairs for each prime that are not
relatively prime and add them up. However, we have an issue of double counting when the primes collide i.e. when counting 2 and 3, we have numbers 6 and 12 which will be 
double counted. To combat this doublecounting, we will in turn, have to the number of pairs which divide 6. 

Still not sure why the magnitudes of the cnts never exceed 1. 

Discussed with Andwerp

if there are not repeated numbers in the prime factorization, then count is 1 if prime factor count is odd, otherwise -1 if prime factor count is even
If there are repeated numbers in the prime factorization, then count is 0.

*/
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
 
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[num]++;
    }
 
    ll res = 0;
 
    for(int i = 2; i < MAXN; i++) {
        ll cnt = cnts[i] + 1;
        ll sum = 0;
        if(cnt != 0) {
            for(int j = 1; j * i < MAXN; j++) {
                sum += a[i * j];
                cnts[i * j] -= cnt;
            }
            res += cnt * sum * (sum - 1) / 2;
        }
    }
 
    cout << n * (n - 1) / 2 - res << '\n';
 
    return 0;
}