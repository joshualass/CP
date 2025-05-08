#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const ll inf = 1e18;

void solve() {
    
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;    

    ll c = 0, g = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            c = 0;
        } else {
            c += a[i];
            c = max(c, 0LL);
            g = max(g, c);
        }
    }

    // cout << "a : " << a << '\n';

    // cout << "g : " << g << '\n';

    if(count(s.begin(), s.end(), '0') == 0) {
        if(g == k) {
            cout << "Yes\n";
            for(ll x : a) cout << x << " ";
            cout << '\n';

        } else {
            cout << "No\n";
        }
        return;
    }

    if(g > k) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";

    int p = -1;
    for(int i = 0; i < n; i++) if(s[i] == '0') p = i;

    ll ml = 0, mr = 0;
    c = 0;
    for(int j = p - 1; j >= 0; j--) {
        if(s[j] == '0') break;
        c += a[j];
        ml = max(ml, c);
    }
    c = 0;
    for(int j = p + 1; j < n; j++) {
        if(s[j] == '0') break;
        c += a[j];
        mr = max(mr, c);
    }

    a[p] = k - ml - mr;
    s[p] = '1';
    for(int i = 0; i < n; i++) {
        cout << (s[i] == '0' ? -inf : a[i]) << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}