#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int SIZE = 1e6+1;

int lowestdivisors[SIZE];

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

void solve() {
    int n, m; cin >> n >> m;
    if(n == 1 || m == 1) { //one person to vote/one option already
        cout << "YES\n";
        return;
    }
    if(m >= n) { //more options than people
        cout << "NO\n";
        return;
    }
    cout << (lowestdivisors[n] > m ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 2; i<= 1e6; i++) {
        if(isPrime(i)) {
            for(int t = 1; t * i < SIZE; t++) {
                if(lowestdivisors[t*i] == 0) {
                    lowestdivisors[t*i] = i;
                }
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) {
        solve();
    }
    return 0;
}