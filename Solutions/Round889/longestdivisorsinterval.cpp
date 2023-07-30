#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
// not a very cool problem D:
 
void solve() {
    ll n; cin >> n;
    ll cnt = 0;
    while(n % ++cnt == 0) {}
    cout << --cnt << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
