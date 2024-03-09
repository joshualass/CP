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
    vector<ll> v(n);

    for(ll &x : v) cin >> x;
    ll sum = reduce(v.begin(),v.end());
    if(sum != sum / n * n) {
        cout << "No\n";
        return;
    }
    ll avg = sum / n;
    vector<ll> radd(32);
    vector<ll> rsub(32);
    vector<ll> cadd(32);
    vector<ll> csub(32);

    bool ok = 1;
    for(int i = 0; i < n; i++) {
        ll diff = avg - v[i];
        if(diff > 0) {
            ll lobit = -1, hibit = -1;
            for(int bit = 0; bit < 32; bit++) {
                if(((diff >> bit) & 1)) {
                    if(lobit == -1) {
                        lobit = bit;
                    }
                    if(hibit != -1 && hibit != bit - 1) {
                        ok = 0;
                    }
                    hibit = bit;
                }
            }
            if(lobit == hibit) {
                cadd[lobit]++;
            } else {
                radd[hibit+1]++;
                rsub[lobit]++;
            }
        }
        if(diff < 0) {
            diff = abs(diff);
            ll lobit = -1, hibit = -1;
            for(int bit = 0; bit < 32; bit++) {
                if(((diff >> bit) & 1)) {
                    if(lobit == -1) {
                        lobit = bit;
                    }
                    if(hibit != -1 && hibit != bit - 1) {
                        ok = 0;
                    }
                    hibit = bit;
                }
            }
            if(lobit == hibit) {
                csub[lobit]++;
            } else {
                rsub[hibit+1]++;
                radd[lobit]++;
            }
        }
    }

    // cout << "is ok ? " << ok << '\n';

    for(int bit = 0; bit < 32; bit++) {
        // cout << "bit : " << bit << '\n';
        // cout << "ra : " << radd << '\n';
        // cout << "rs : " << rsub << '\n';
        // cout << "ca : " << cadd << '\n';
        // cout << "cs : " << csub << '\n';
        ll m = min(radd[bit],rsub[bit]);
        radd[bit] -= m;
        rsub[bit] -= m;
        if(radd[bit] > 0) {
            int m1 = min(cadd[bit], radd[bit]);
            radd[bit] -= m1;
            cadd[bit] -= m1;
            radd[bit+1] += m1;
            if(csub[bit] < radd[bit]) {    
                ok = 0; 
                // cout << "notok1\n";
            }
            csub[bit] -= radd[bit];
            radd[bit] = 0;
        }
        if(rsub[bit] > 0) {
            int m1 = min(csub[bit], rsub[bit]);
            rsub[bit] -= m1;
            csub[bit] -= m1;
            rsub[bit+1] += m1;
            if(cadd[bit] < rsub[bit]) {    
                ok = 0; 
                // cout << "notok2\n";
            }
            cadd[bit] -= rsub[bit];
            rsub[bit] = 0;
        }
        m = min(cadd[bit],csub[bit]);
        cadd[bit] -= m;
        csub[bit] -= m;
        if(cadd[bit] > 0) {
            if(cadd[bit] & 1) {    
                ok = 0; 
                // cout << "notok3\n";
            }
            radd[bit+1] += cadd[bit] / 2;
            cadd[bit] = 0;
        }
        if(csub[bit] > 0) {
            if(csub[bit] & 1) {    
                ok = 0; 
                // cout << "notok4\n";
            }
            
            rsub[bit+1] += csub[bit] / 2;
            csub[bit] = 0;
        }
    }
    // cout << "ending\n";
    // cout << "ra : " << radd << '\n';
    // cout << "rs : " << rsub << '\n';
    // cout << "ca : " << cadd << '\n';
    // cout << "cs : " << csub << '\n';
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}