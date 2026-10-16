#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

/*
not very locked in ;p
at least solved ? 
bad for loop and not locked in. feeling out of control on these interactive problems; caution needs to be exercised. 
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int debug = 0;
// const int debug = 1;

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    if(debug == 0) {
        for(ll &x : a) cin >> x;
    } else {
        a.assign(n, n);
    }

    clock_t tStart = clock();

    // printf("Time taken0: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    vector<ll> p(n);
    iota(p.begin(), p.end(), 0);

    auto ask = [&](vector<ll> q) -> void {
        assert(sz(q) == n);
        ll w;
        if(debug == 0) {
            cout << "? " << q << endl;
            cin >> w;
            if(w == -1) assert(0);
        } else {
            w = accumulate(q.begin(), q.end(), 0LL) * 7;
        }
        ll expected = accumulate(q.begin(), q.end(), 0LL) * 7;
        ll skip = expected - w;
        erase_if(p, [&](const auto x) -> bool {
            return q[x] != skip;
        });
    };

    sort(p.begin(), p.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return a[lhs] < a[rhs];
    });

    auto test_assignment = [&](ll g) -> vector<ll> {

        // cout << "g : " << g << endl;
        assert(g <= 17);

        ll pt = 0;
        vector<ll> q(n);

        ll ops = 0;

        for(ll i = 0; pt < sz(p); i++) {
            // cout << "i : " << i << endl;
            ops++;
            for(ll j = (g == 1 ? i : 0); j <= i; j++) {
                ops++;
                ll prev = 1, fill_to = 1;
                
                for(ll k = 0; k < g - 1; k++) {
                    prev *= i;
                    fill_to *= (i + 1);
                    ops++;
                }

                if(i == j) {
                    prev = 0;
                    ops++;
                }

                // cout << "j : " << j << " prev : " << prev << " ft : " << fill_to << endl;
                
                for(ll k = prev + 1; k <= fill_to && pt < sz(p); k++) {
                    ops++;
                    if(a[p[pt]] >= i) {
                        q[p[pt]] = j;
                        pt++;
                    } else {
                        return {};
                    }
                }
            }
        }
        // cout << "g : " << g << " ops : " << ops << endl;
        return q;
    };

    ll ops = 1;
    while(test_assignment(ops).empty()) ops++;

    // printf("Time taken1: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    // cout << "ops : " << ops << endl;

    while(sz(p) > 1) {
        // cout << "p : " << p << endl;
        assert(ops >= 1);
        ask(test_assignment(ops--));
        // cout << "after p : " << p << endl;
    }

    assert(sz(p) == 1);
    cout << "! " << p[0] + 1 << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    for(ll i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}