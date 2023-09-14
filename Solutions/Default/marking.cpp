#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        ll n, d, k; cin >> n >> d >> k;
        d = d % n;
        if(k <= (d + 1) * n % d) {
            cout << (n / (d + 1) / k) + ((n % (d + 1)) * d) % n << '\n';
        } else {
            cout << ((n % (d + 1)) / k + (n / d) + ((n % d) * d)) % n<< '\n';
        }
    }

    return 0;
}