#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        ll n; cin >> n;
        if(n < 0) {
            cout << n << " " << (n * -1) - 1 << '\n';
        } else if(n == 0) {
            cout << "-1 0 1\n";
        } else {
            cout << (n * -1 + 1) << " " << n << '\n';
        }
    }

    return 0;
}