#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int SIZE = 32000;
bool primes[SIZE];

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < SIZE; i++) {
        if(isPrime(i)) {
            primes[i] = true;
        }
    }
    int num; cin >> num;
    while(num != 4) {
        int reductions = 1;
        while(!isPrime(num)) {
            int sum = 0;
            while(!isPrime(num)) {
                for(int i = 2; i < SIZE; i++) {
                    if(primes[i]) {
                        if(num % i == 0) {
                            sum += i;
                            num /= i;
                            break;
                        }
                    }
                }
            }
            // cout << num << "\n";
            num += sum;
            reductions++;
        }
        cout << num << " " << reductions << "\n";
        cin >> num;
    }

    return 0;
}