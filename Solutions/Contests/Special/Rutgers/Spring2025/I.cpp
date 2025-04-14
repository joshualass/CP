#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
ways alice can win
1. bob does not have move 2
2. move does not have move 4

else bob rats out

when can bob not have move 2? 
when lhs and rhs length < b

when can bob not have move 4?
after splitting middle, each side has precisely a turn from each

should work :) ?

*/

void solve() {
    
    int a, b, n; cin >> a >> b >> n;
    int rem = n - a;
    int lhs = rem / 2, rhs = (rem + 1) / 2;

    int awin = 0;
    if(lhs < b && rhs < b) awin = 1;
    if(lhs >= a && lhs < b * 2 && rhs >= a && rhs < b * 2) awin = 1;

    cout << (awin ? "Alice" : "Bob") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}