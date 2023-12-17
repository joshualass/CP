#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;


void pari_forced(ll num_blocks) {
    if (num_blocks % 2 == 0) {
        cout << "RYAN" << endl;
    } else {
        cout << "PHEBE" << endl;
    } 
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    ll n, q; cin >> n >> q;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    ll num_blocks = 0, totwei = 0;

    for (ll i = 1; i <= n; ++i) {
        ll x = a[i];
        num_blocks += x;
        totwei += i * x;
    }

    set<pair<ll, int>> blocks;

    for (int i = 1; i <= n; ++i) {
        blocks.insert({a[i], i});
    }

    while (q--) {
        string s; cin >> s;
        if (s == "?") {
            // game on
            ll k; cin >> k;
            if (k > totwei) {
                pari_forced(num_blocks);
            } else if (k == totwei) {
                pari_forced(num_blocks + 1);
            } else {
                // most frequent block
                auto p = *blocks.rbegin();
                ll freq = p.first, wei = p.second;
                // cerr << "freq : " << freq << " wei : " << wei << endl;
                // is this >= half amount of total

                ll diff = totwei - k;

                if (diff % wei != 0) {
                    // parity forced
                    pari_forced(num_blocks); 
                    continue;
                }

                // cerr << "diff : " << diff << endl;


                ll rem_blocks = diff / wei;

                // cerr << "rem_blocks : " << rem_blocks << endl;

                if (rem_blocks > freq) {
                    pari_forced(num_blocks);
                    continue; 
                }

                ll can_use = freq - rem_blocks;

                if (can_use < num_blocks - freq) {
                    pari_forced(num_blocks);
                    continue;
                }

                // cerr << "can_use : " << can_use << endl;

                pari_forced(num_blocks - rem_blocks + 1); 
                
            }
        } else {
            // set
            ll ind; cin >> ind;
            ll x; cin >> x;
            blocks.erase({a[ind], ind});
            num_blocks -= a[ind];
            totwei -= a[ind] * ind;
            a[ind] = x;
            num_blocks += a[ind];
            totwei += a[ind] * ind;
            blocks.insert({a[ind], ind});
        }
    }

    

    
    return 0;
}