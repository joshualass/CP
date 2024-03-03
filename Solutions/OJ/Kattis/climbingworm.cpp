#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, h; cin >> a >> b >> h;
    int curr_h = 0;
    int turns = 0;
    while(1) {
        turns++;
        curr_h += a;
        if(curr_h >= h) break;
        curr_h -= b;
    }
    cout << turns << '\n';
    return 0;
}