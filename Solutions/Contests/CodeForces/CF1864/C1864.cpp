#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n; cin >> n;
    int cnt = 1;
    string out = "";
    while(n != 1) {
        ll div = 1;
        while(n % (div * 2) == 0) {
            div *= 2;
        }
        if(div == n) {
            while(n != 1) {
                cnt++;
                // cout << n << " ";
                out += to_string(n) + " ";
                n /= 2;
            }
            
        } else {
            // cout << n << " ";
            cnt++;
            out += to_string(n) + " ";
            n -= div;
        }
    }
    cout << cnt << "\n";
    cout << out << n << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}