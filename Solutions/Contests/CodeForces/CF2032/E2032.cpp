#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int hi = *max_element(a.begin(), a.end());
    vector<ll> cp(n * 3);
    for(int i = 0; i < n; i++) {
        cp[i+3] += hi - a[i];
        cp[i+n+2] -= hi - a[i];
    }

    // cout << "cp : " << cp << '\n';
    ll c = 0;
    vector<ll> cpd(n);
    for(int i = 0; i < n * 3; i += 2) {
        c += cp[i];
        cpd[i%n] += c;
    }
    for(int i = 1; i < n * 3; i += 2) {
        c += cp[i];
        cpd[i%n] += c;
    }
    // cout << "cp dist : " << cpd << '\n';
    vector<ll> res(n);
    vector<ll> stops(n*2);
    ll a0 = 0;
    for(int i = 0; i < n * 2; i += 2) {
        if(i < n) {
            if(i + n - 1 < n * 2) {
                stops[i + n - 1] += cpd[i];
            }
            a0 += cpd[i];
        }
        a0 -= stops[i];
        res[i % n] += a0;
    }
    a0 = 0;
    for(int i = 1; i < n * 2; i += 2) {
        if(i < n) {
            if(i + n - 1 < n * 2) {
                stops[i + n - 1] += cpd[i];
            }
            a0 += cpd[i];
        }
        a0 -= stops[i];
        res[i % n] += a0;
    }
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n / 2; j++) {
    //         res[(i + j * 2) % n] += cpd[i];
    //     }
    // }
    for(int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
    // for(int i = 0; i < n; i++) {
    //     a[i] += res[i] * 2;
    //     a[(i+1)%n] += res[i];
    //     a[(i-1+n)%n] += res[i];
    // }
    // cout << "resulting a : " << a << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}