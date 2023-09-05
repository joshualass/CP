#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;
const int SIZE = 1e6 + 1;
int primes[SIZE];

bool prime(int n) {
    if(n <= 1) {
        return false;
    }
    if(n == 2 || n == 3) {
        return true;
    }
    if(n % 2 == 0 || n %3 == 0) {
        return false;
    }
    for(int i = 5; i <= sqrt(n); i += 6) {
        if(n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i = 0; i <= 1e6; i++) {
        if(prime(i)) {
            primes[i] = 1;
        }
    }

    
    

    return 0;
}