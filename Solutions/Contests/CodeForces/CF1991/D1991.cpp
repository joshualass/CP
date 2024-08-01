#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
If 2 were not a prime number, then we can alternately label all nodes 1's and 2's because 2 numbers of same parity xored will have an even output and 2 is the only prime number. 
However, 2 is prime and so for large n, we see that 2 numbers % 4 xored together will have a number divisible by 4 as output, so we just label nodes 1, 2, 3, 4 ...
*/

void solve() {
    int n; cin >> n;
    if(n < 6) {
        vector<int> bruh = {1, 2, 2, 3, 3};
        if(n == 1) {
            cout << "1\n";
        } else if(n <= 3) {
            cout << "2\n";
        } else {
            cout << "3\n";
        }
        for(int i = 0; i < n; i++) {
            cout << bruh[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "4\n";
        for(int i = 0; i < n; i++) {
            cout << i % 4 + 1 << " \n"[i == n - 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}