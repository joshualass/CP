#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll ask(ll l, ll r) {
    cout << "xor " << l << " " << min((ll)1e18,r) << endl;
    ll x; cin >> x;
    return x;
}

vector<ll> solver(ll cur, ll nextbit, int inrange, ll parent_query) {
    ll isset = ((parent_query >> nextbit) & 1);
    ll add = (1LL - isset) << nextbit;
    ll lo_query = ask(cur + add, cur + add + ((1LL << nextbit) - 1));
    if(inrange == 3) {
        if(lo_query) {
            vector<ll> solve2 = solver(cur + add, nextbit - 1, 2, lo_query);
            solve2.push_back(parent_query ^ lo_query);
            return solve2;
        } else {
            return solver(cur + (1LL << isset), nextbit - 1, 3, lo_query);
        }
    } else if(inrange == 2) {
        if(lo_query) {
            return {lo_query, parent_query ^ lo_query};
        } else {
            return solver(cur + (1LL << isset), nextbit - 1, 2, parent_query);
        }
    }
}

void solve() {
    
    ll start = ask(1,1e18);
    vector<ll> res;
    if(__builtin_popcountll(start) && ask(1LL << (63 - __builtin_clzll(start)), (1LL << (64 - __builtin_clzll(start))) - 1) == start) {
        res = solver(0LL, 60, 3, start);
    } else {
        for(int bit = 60; bit >= 1; bit++) {
            ll askrange = ask(1LL << bit, (1LL << (bit + 1)) - 1);
            if(askrange) {
                if(ask(askrange,askrange) == askrange) {
                    for(int bbit = bit - 1; bbit >= 1; bbit--) {
                        ll askrange2 = ask(1LL << bbit, (1LL << (bbit + 1)) - 1);
                        if(askrange2) {
                            if(ask(askrange2,askrange2) == askrange2) {
                                res = {askrange, askrange2, start ^ askrange ^ askrange2};
                            } else {
                                res = solver(1LL << bbit, bbit - 1, 2, askrange2);
                                res.push_back(askrange);
                            }
                        }
                    }
                } else {
                    res = solver(1LL << )
                }

                break;
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}