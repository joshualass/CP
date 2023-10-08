#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    if(k > n + 1) { //k is too large
        cout << "0\n";
    } else if(k == 1) {
        cout << "1\n"; //case where only possibility is all 0's, n and m don't matter here
    } else if(k == 2) {
        cout << (min(m,n - 1) + m / n) << "\n"; //case where n + 1 values can be values from 1 - (n - 1) + nonzero values divisible by n
    } else if(k == 3) {
        cout << max(0LL, m - n - (m-n)/n) << "\n"; //m can be any value where it is greater than n and not divisible by n
    } else {
        cout << "0\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}