#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
nim
all odd stacks must split into an even an odd stack
if all stacks are odd, this is losing because other player can chop make this state happen again no matter what type of operation is done
however, if there is one even, then we can leverage this even to make the next state all odd, so this is a winning state
the remaining case is for all even stones
if there are an even # of piles, then player can make these all even and win
now, we are at a case where we have an odd number of piles with an even number of stones. 
Now, the objectives for both players is to maintain that there are only even stones left. 
Thus, we can divide all the stone piles by 2 and get the output of this subproblem after dividing by 2. If a player can't make a move for the divided by 2 scenario, then it's the equivalent of the move 
making an odd pile and having the other player win. 
*/

void solve() {
    
    int n; cin >> n;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto win = [](auto self, vector<ll> stones) -> bool {
        int all_odd = 1;
        for(ll x : stones) if(x % 2 == 0) all_odd = 0;
        if(all_odd) return 0;
        for(ll x : stones) if(x & 1) return 1;
        if(stones.size() % 2 == 0) return 1;
        //now all stones are even, and we have an odd count of them
        for(ll &x : stones) x /= 2;
        return self(self, stones);
    };  

    cout << win(win, a) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}