#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m, k; cin >> n >> m >> k;

    vector<set<ll>> rp(n);
    vector<set<ll>> cp(m);

    for(int i = 0; i < n; i++) {
        rp[i].insert(-1);
        rp[i].insert(m);
    }
    for(int i = 0; i < m; i++) {
        cp[i].insert(-1);
        cp[i].insert(n);
    }

    ll rlop = 0;
    ll rhip = n;
    ll clop = -1;
    ll chip = m;

    for(int i = 0; i < k; i++) {
        ll r, c; cin >> r >> c;
        r--; c--;
        rp[r].insert(c);
        cp[c].insert(r);
    }
    
    ll cnt = k + 1;
    ll curr = 0, curc = 0;

    for(int i = 0; i < 1e6; i++) {
        // cout << "curr : " << curr << " curc : " << curc << " cnt : " << cnt << '\n';
        int nextr, nextc;
        switch(i % 4) {
            case 0 : //same r, increasing col
                nextr = curr;
                nextc = max(min(chip, *rp[curr].upper_bound(curc)) - 1, curc);
                chip = nextc;
                break;
            case 1 : //same col, increasing r
                nextc = curc;
                nextr = max(min(rhip, *cp[curc].upper_bound(curr)) - 1, curr);
                rhip = nextr;
                break;
            case 2 : //same row, decreasing col
                nextr = curr;
                nextc = min(max(clop, (*--rp[curr].upper_bound(curc))) + 1, curc);
                clop = nextc;
                break;
            case 3 : //same col, decreasing row
                nextc = curc;
                // cout << "rlop : " << rlop << " clo[cur]c : " << clo[curc] << " curr : " << curr << '\n';
                nextr = min(max(rlop, (*--cp[curc].upper_bound(curr))) + 1, curr);
                rlop = nextr;
                break;
        }

        if(curr == nextr && curc == nextc && !(curr == 0 && curc == 0)) break;
        cnt += abs(nextr-curr) + abs(nextc-curc);
        curr = nextr;
        curc = nextc;
    }
    // cout << cnt << '\n';
    cout << (cnt == n * m ? "Yes" : "No") << '\n';

    return 0;
}