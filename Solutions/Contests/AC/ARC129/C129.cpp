#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

ll ext_gcd ( ll A, ll B, ll *X, ll *Y ){
    ll x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

ll modInv ( ll a, ll m ) {
    ll x, y;
    ext_gcd( a, m, &x, &y );
 
    // Process x so that it is between 0 and m-1
    x %= m;
    if ( x < 0 ) x += m;
    return x;
}

pair<ll,ll> largest_triangle(ll n) {
    ll ans = 1;
    while((ans + 1) * (ans + 2) / 2 <= n) {
        ans++;
    }
    return {ans, (ans) * (ans + 1) / 2};
}

ll get_digit(ll idx) { //this number % 7 at this place is 1
    ll num = 1;
    for(int i = 0; i < idx; i++) { //0-indexed 
        num *= 10;
        num %= 7;
    }
    return modInv(num,7);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;

    vector<string> ans;
    ll digit = 0;

    while(n != 0) {
        string add = "";
        if(ans.size()) {
            add.push_back('0' + get_digit(digit));
            digit++;
        }
        pair<ll,ll> p = largest_triangle(n);
        for(int i = 0; i < p.first; i++) {
            add.push_back('7');
        }
        reverse(add.begin(),add.end());
        ans.push_back(add);
        digit += p.first;
        // cout << "n: " << n << " p: " << p << '\n';
        n -= p.second;
    }

    reverse(ans.begin(),ans.end());

    for(auto x : ans) cout << x;

    return 0;
}