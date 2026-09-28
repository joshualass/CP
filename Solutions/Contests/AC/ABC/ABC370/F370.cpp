#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int lifts[400000][20];

ll count_possible_edges(vector<ll> &a, ll m, ll k) {

    // cout << "m : " << m << '\n';

    int lo = 0;
    ll sum = 0;
    for(int i = 0; i < a.size() * 2; i++) {
        sum += a[i % a.size()];

        while(sum - a[lo % a.size()] >= m) {
            sum -= a[lo % a.size()];
            lo++;
        }

        if(sum >= m) {
            lifts[i][0] = lo;
        } else {
            lifts[i][0] = -1;
        }

        // cout << "i : " << i << " lifts[i][0] : " << lifts[i][0] << '\n';

    }

    auto go = [&](int i, int j) -> int {
        i--;
        if(i <= -1) return -1;
        return lifts[i][j];
    };

    for(int j = 1; j < 20; j++) {
        for(int i = 0; i < a.size() * 2; i++) {
            lifts[i][j] = go(go(i + 1,j-1),j-1);
            // cout << "i : " << i << " j : " << j << " lifts[i][j] : " << lifts[i][j] << '\n';
        }
    }

    int cntok = 0;

    for(int i = a.size(); i < a.size() * 2; i++) {
        int cur = i + 1;
        for(int j = 19; j >= 0; j--) {
            if((k >> j) & 1) {
                // cout << "j : " << j << "GOGO\n";
                cur = go(cur,j);
            }
        }

        // cout << "i : " << i << " cur : " << cur << '\n';

        if(cur >= i + 1 - (int) a.size()) {
            cntok++;
        }

    }

    return cntok;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    vector<ll> a(n);

    for(ll &x : a) cin >> x;

    // count_possible_edges(a, 2, 2);


    ll l = 1, r = 1e10;
    while(l != r) {
        ll m = (l + r + 1) / 2;

        int cntposs = count_possible_edges(a, m, k);

        // cout << "m : " << m << " cnt poss : " << cntposs << '\n';

        if(cntposs) {
            l = m;
        } else {
            r = m - 1;
        }

    }

    cout << l << " " << n - count_possible_edges(a,l,k) << '\n';

    return 0;
}