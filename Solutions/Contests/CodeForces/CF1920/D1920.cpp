#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
clock_t tStartl;
struct op {
    ll type;
    vector<ll> a;
    ll b;
    ll l;
    op(ll type, vector<ll> a, ll b, ll l) {
        this->type = type;
        this-> a = a;
        this->b = b;
        this->l = l;
    }


};

void solve() {

    int n, q; cin >> n >> q;
    bool prev = 1;
    vector<op> a;
    ll l = 0;
    for(int i = 0; i < n; i++) {
        ll b, x; cin >> b >> x;
        // cout << "l : " << l << '\n';
        if(l < 1e18) {
            if(b == 1) {
                if(a.empty() || a.back().type == 2) {
                    a.push_back(op(1,{x},1,l + 1));
                } else {
                    a.back().a.push_back(x);
                    a.back().l++;
                }
                l++;
            } else {
                // __int128_t res = (__int128_t) x * (__int128_t) l;
                // ll res = x * l;
                // cout << "l : " << l << " x : " << x << " l * x / x : " << (res) / x << '\n';
                // if(res > 1e18) {
                    // x = (1e18 + l - 1) / l;
                // }
                if(l > 1e18 / (x + 1)) {
                    x = (1e18 + l - 1) / l;
                }
                // cout << "x : " << x << '\n';
                a.push_back(op(2,{},x+1,l * (x + 1)));
                l *= x + 1;
            }
        }
    }
    // if(a[0].a[0] == 68261) {
    //     cout << "as:" << a.size() << '\n';
    //     cout << "Time taken : " << fixed << setprecision(2) << (double)(clock() - tStartl)/CLOCKS_PER_SEC;
    //     // printf("Time taken: %.2fs\n", (double)(clock() - tStartl)/CLOCKS_PER_SEC);
    // }
    // cout << "l : " << l << '\n';
    // cout << "as : " << a.size() << '\n';
    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        ll ans = -1;
        for(int j = a.size() - 1; j >= 0; j--) {
            // cout << "j : " << j << " k : " << k << '\n';
            // op o = a[j];
            if(a[j].type == 1) {
                if(k > a[j].l - a[j].a.size()) {
                    ans = a[j].a[k - (a[j].l - a[j].a.size()) - 1];
                    break;
                }
            } else {
                k = (k - 1) % (a[j].l / a[j].b) + 1;
            }
        }
        cout << ans << " \n"[i == q - 1];
    }

    // int n, q; cin >> n >> q;

    // vector<pair<int,vector<ll>>> ops;
    // for(int i = 0; i < n; i++) {
    //     int type; cin >> type;
    //     int num; cin >> num;
    //     if(type == 1) {
    //         if(ops.empty() || ops.back().first == 2) {
    //             ops.push_back({1,{num}});
    //         } else {
    //             ops.back().second.push_back(num);
    //         }
    //     } else {
    //         ops.push_back({2,{num}});
    //     }
    // }

    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    tStartl = clock();
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}