#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ll bruteforcer(vector<ll> a) {
    ll res = 0;
    for(int i = 0; i < a.size(); i++) {
        for(int j = i; j < a.size(); j++) {
            ll t = a[i] + a[j];
            while(t % 2 == 0) t /= 2;
            res += t;
        }
    }

    return res;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    // iota(a.begin(),a.end(), 1);
    for(ll &x : a) cin >> x;
    // int n = 100;
    // vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        // a[i] = rng() % 100 + 1;
    }
    ll res = accumulate(a.begin(), a.end(), 0LL) * (n + 1);

    // cout << "start res : " << res << '\n';
    
    for(int i = 1; i <= 25; i++) {
        vector<ll> sums(1 << i);
        vector<ll> cnts(1 << i);
        for(ll x : a) {
            ll idx = x % (1 << i);
            sums[idx] += x;
            cnts[idx]++;
        }

        for(int j = 0; j <= 1 << (i - 1); j++) {
            if(j % (1 << (i - 1)) == 0) {
                res -= (sums[j] * (cnts[j] + 1)) >> i;
                // if(sums[j]) cout << "i : " << i << " same sub : " << ((sums[j] * (cnts[j] + 1)) >> i) << '\n';
            } else {

                ll leftsum = sums[j], rightsum = sums[(1 << i) - j];
                ll leftcnt = cnts[j], rightcnt = cnts[(1 << i) - j];

                // if(leftsum && rightsum) {
                //     cout << "i : " << i << '\n';
                //     cout << "lsum : " << leftsum << " rsum : " << rightsum << '\n';
                //     cout << "lcnt : " << leftcnt << " rcnt : " << rightcnt << '\n';
                // }

                res -= leftcnt * rightcnt;
                leftsum -= leftcnt * j;
                rightsum -= rightcnt * ((1 << i) - j);
                // if(leftsum && rightsum) {
                //     cout << "sumafter\n";
                //     cout << "i : " << i << '\n';
                //     cout << "lsum : " << leftsum << " rsum : " << rightsum << '\n';
                //     cout << "lcnt : " << leftcnt << " rcnt : " << rightcnt << '\n';
                // }
                res -= (leftsum * rightcnt + rightsum * leftcnt) >> i;  
            }
        }
    }

    cout << res << '\n';

    // cout << "bruteforc res : " << bruteforcer(a) << '\n';

    return 0;
}