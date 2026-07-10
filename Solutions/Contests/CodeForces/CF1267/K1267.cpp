#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

const int testing = 0;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, multiset<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

ll c[20][20];

void pc() {
    for(ll i = 0; i < 20; i++) {
        for(ll j = 0; j <= i; j++) {
            if(j == 0) {
                c[i][j] = 1;
            } else {
                c[i][j] = c[i-1][j-1] + c[i-1][j];
            }
            // cout << c[i][j] << " ";
        }
        // cout << '\n';
    }
}

ll solve(ll n) {

    // map<ll,ll> f;
    ll cnt = 0;

    vector<ll> a(20);

    for(ll i = 2; n; i++) {
        a[n % i]++;
        n /= i;
        cnt++;
    }

    // cout << "a : " << a << endl;

    
    ll ans = 0;
    for(ll i = 1; i <= cnt; i++) {
        if(a[i]) {
            a[i]--;
            ll res = 1;
            ll avail = 0;
            for(ll j = cnt - 1; j >= 0; j--) {
                if(j) avail++;
                // assert(a[i] <= avail);
                res *= c[avail][a[j]];
                avail -= a[j];
            }
            a[i]++;
            if(avail) res = 0;
            ans += res;
            // cout << "i : " << i << " res : " << res << endl;
        }
    }

    cout << ans - 1 << '\n';
    return ans;
}

ll solve_slow(ll n) {
    vector<ll> gg;
    int z = 2;
    while(n) {
        gg.push_back(n % z);
        n /= z++;
    }

    sort(gg.begin(), gg.end());

    set<ll> nums;

    while(1) {
        ll ok = 1;
        for(ll i = 0; i < sz(gg); i++) {
            if(gg[i] >= i + 2) ok = 0;
        }
        // cnt += ok;
        // if(ok) s.insert(gg);
        if(ok && gg.back()) {
            ll res = 0;
            ll mul = 1;
            for(ll i = 0; i < sz(gg); i++) {
                res += gg[i] * mul;
                mul *= i + 2;
            }
            // cout << "res : " << res << endl;
            nums.insert(res);
        }
        if(!next_permutation(gg.begin(), gg.end())) break;
    }

    // cout << sz(s) << '\n';
    cout << sz(nums) << endl;

    multiset<ll> huh(gg.begin(), gg.end());
    for(ll x : nums) {
        multiset<ll> check;
        ll cur = 2;
        ll t = x;
        while(x) {
            check.insert(x % cur);
            x /= cur;
            cur++;
        }
        if(check != huh) {
            cout << "x : " << t << endl;
            cout << "check : " << check << " huh : " << huh << endl;
        }
        assert(check == huh);
    }

    return sz(nums);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pc();

    if(testing) {
        for(int i = 1; i < 50; i++) {
            ll slow = solve_slow(i);
            ll fast = solve(i);
    
            if(slow != fast) {
                cout << "diff i : " << i << " slow : " << slow << " fast : " << fast << endl;
                assert(0);
            }
        }
    } else {
        ll casi; cin >> casi;
        // while(casi-->0) solve();
        while(casi-->0) {
            ll n; cin >> n;
            solve(n);
        }
    }



    return 0;
}