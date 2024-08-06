#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//the primary issue is that we want to avoid double counting some of the prime numbers. i.e. if we have 6 6, we may think that there are 2 coprime pairs because they share coprime factors
//Solution: Use Euler's totient function

const int MAXN = 1e6;
int phi[MAXN + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i <= MAXN; i++) {
        phi[i] = i;
    }

    for(int i = 1; i <= MAXN; i++) {
        for(int j = 2; i * j <= MAXN; j++) {
            phi[i * j] -= phi[i];
        }
    }

    for(int i = 0; i < 50; i++) {
        cout << "i : " << i << " phi[i] : " << phi[i] << '\n';
    }

    return 0;
}