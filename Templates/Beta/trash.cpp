#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

int countprimes(int h) {
    int c = 0;
    for(int i = 1; i <= h; i++) {
        if(isPrime(i)) c++;
    }
    return c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    while(tc--) {
        int h; cin >> h;
        cout << countprimes(h) << '\n';
    }

    return 0;
}