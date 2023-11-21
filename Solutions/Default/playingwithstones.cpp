// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4228
/* 2 observations to make 
if a number is odd, we can do floor division on the number until it's even.
This represents the other player optimally picking the number of stones to 'rebalance' the number
i.e. if you start with 11 stones, no matter which amount (1-5) a player picks from this pile, the other player can balance to 56 - (first player's 1-5)
we are left with even numbers now.
take the xor of all the even numbers and if this is zero, then all states are controllable by player two
when player 1 makes a move, the xor of the number changes. player 2 will pick a stone, such that the xor of the numbers is back to 0
repeat this process ... nice problem
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll transform(ll num) {
    while(num & 1) num >>= 1;
    return num;
}

void solve() {
    int n; cin >> n;

    ll curr = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        curr ^= transform(num);
    }
    cout << (curr == 0 ? "NO" : "YES") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}