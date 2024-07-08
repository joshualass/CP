#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//if it is your turn and s_i is some number, whether you win or not

//trying to force win, all states after e are win
bool afterwin(ll s, ll e) {

    if(s > e) return 1;

    //if end is at an odd pos, meaning first win is even, then having even position is losing
    //every turn after you make even, opponent makes odd ...
    if(e & 1) {
        return s % 2 == 0;
    }

    //e is even now
    ll last_alternate = e / 2 + 1;
    if(s >= last_alternate) {
        return s & 1;
    }

    ll lowest_loss = (last_alternate + (last_alternate & 1 ? 1 : 0));

    return afterwin(s, lowest_loss / 2 - 1);

}

//trying to force win, all states after e are loss
bool afterloss(ll s, ll e) {

    if(s > e) return 0;

    ll smallest_win = (e + 2) / 2;

    return afterwin(s, smallest_win - 1);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(ll s = 1; s <= 20; s++) {
    //     cout << "s : " << s << " win ? " << afterwin(s,16) << '\n';
    // }

    int n; cin >> n;
    array<int,2> res = {1,0};

    //you win if you are able to visit a losing state 
    for(int i = 0; i < n; i++) {
        // cout << "i : " << i << " res : " << res[0] << " " << res[1] << '\n';
        ll s, e; cin >> s >> e;
        array<int,2> next = {0,0};
        if(res[0]) { //possible to force being first this game
            if(afterwin(s,e)) { //we don't want to go to a state greater than e because that is winning
                next[0] = 1;
            }
            if(afterloss(s,e)) { //the opposite
                next[1] = 1;
            }
        }
        if(res[1]) { //we are interested in what can't be done by first player
            if(!afterwin(s,e)) { //if first player can't force another win, then we can force a win
                next[0] = 1;
            }
            if(!afterloss(s,e)) { //the opposite
                next[1] = 1;
            }
        }
        swap(next[0],next[1]); //bruh
        res = next;
    }

    // cout << "i : " << n << " res : " << res[0] << " " << res[1] << '\n';
    swap(res[0],res[1]); // bruh bruh
    cout << res[0] << " " << res[1] << '\n';


    return 0;
}