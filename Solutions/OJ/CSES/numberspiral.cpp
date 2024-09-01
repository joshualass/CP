#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
 
    int n;
    cin >> n;
 
    while(n-->0) {
        ll r,c;
        cin >> r >> c;
        ll high = max(r,c);
        if(high % 2 == 1) {
            ll temp = r;
            r = c;
            c = temp;
        }
        if(r == high) {
            ll out = high * high - c + 1;
            cout << out << "\n";
        } else {
            ll out = (high-1) * (high-1) + r;
            cout << out << "\n";
        }
    }
 
    return 0;
}