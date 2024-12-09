#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
good reminder to prove solutions and think more before starting to code. 
handle lots of cases. then correctly calculate the cycle size. ok to do some extra math here. 
*/

void solve() {

    string s, x, y; cin >> s >> x >> y;
    if(count(y.begin(), y.end(), '1') > count(x.begin(), x.end(), '1')) {
        swap(x,y);
    }
    //have more t strings in string x now. 
    ll x0 = count(x.begin(), x.end(), '0'), x1 = count(x.begin(), x.end(), '1'), y0 = count(y.begin(), y.end(), '0'), y1 = count(y.begin(), y.end(), '1'); 
    if(x0 == y0) { //strings have equal number of s strings
        cout << "Yes\n";
        return;
    }

    ll size_diff = (ll) s.size() * (y0 - x0);
    if(size_diff < 0 || x1 == y1) {
        cout << "No\n";
        return;
    }

    if(size_diff % (x1-y1) != 0) {
        cout << "No\n";
        return;
    }

    ll t_size = size_diff / (x1 - y1);

    ll cycle_size = t_size % s.size();
    if(cycle_size == 0) {
        cout << "Yes\n";
        return;
    }

    // if(s.size() % cycle_size != 0) {
    //     cout << "No\n";
    //     return;
    // }

    cycle_size = gcd(s.size(), cycle_size);

    bool ok = 1;
    for(ll i = 0; i < s.size() / cycle_size; i++) {
        for(ll j = 0; j < cycle_size; j++) {
            if(s[j] != s[i*cycle_size + j]) {
                ok = 0;
            }
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// mt19937 rng;

// bool isprime(ll num) {
//     if(num <= 1) return 0;
//     if(num == 2 || num == 3) return 1;
//     if(num % 2 == 0 || num % 3 == 0) return 0;
//     for(ll i = 5; i <= sqrt(num); i++) {
//         if(num % i == 0 || num % (i + 2) == 0) return 0;
//     }
//     return 1;
// }

// ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
//     while(1) {
//         ll num = (rng() % (r - l + 1)) + l;
//         if(isprime(num)) return num;
//     }
// }

// ll M1, M2, B1, B2;
// struct stringhash {
//     vector<ll> h1, h2;
//     vector<ll> p1, p2;
//     ll n;

//     stringhash(string s) {
//         this->n = s.size();
//         p1.push_back(1);
//         for(ll i = 0 ; i < n; i++) {
//             p1.push_back(p1.back() * B1 % M1);
//         }
//         p2.push_back(1);
//         for(ll i = 0 ; i < n; i++) {
//             p2.push_back(p2.back() * B2 % M2);
//         }
//         h1.push_back(0);
//         for(ll i = 0; i < n; i++) {
//             h1.push_back((h1[i] * B1 + s[i]) % M1);
//         }
//         h2.push_back(0);
//         for(ll i = 0; i < n; i++) {
//             h2.push_back((h2[i] * B2 + s[i]) % M2);
//         }
//     }

//     ll get_hash(ll l, ll r) { //[l,r) because that's the cool, Andwerp way
//         ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1 % M1;
//         ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2 % M2;
//         return num1 + num2 * M1;
//     }

// };

// void buildsh() {
//     rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
//     M1 = gen_prime(900000000,1000000000);
//     B1 = gen_prime(9000,10000);
//     M2 = gen_prime(900000000,1000000000);
//     B2 = gen_prime(9000,10000);
// }

// void solve() {
//     string s, x, y; cin >> s >> x >> y;
//     if(count(y.begin(), y.end(), '1') > count(x.begin(), x.end(), '1')) {
//         swap(x,y);
//     }
//     //have more t strings in string x now. 
//     ll x0 = count(x.begin(), x.end(), '0'), x1 = count(x.begin(), x.end(), '1'), y0 = count(y.begin(), y.end(), '0'), y1 = count(y.begin(), y.end(), '1'); 
//     if(x0 == y0) { //strings have equal number of s strings
//         cout << "Yes\n";
//         return;
//     }

//     ll size_diff = (ll) s.size() * (y0 - x0);
//     if(size_diff < 0 || x1 == y1) {
//         cout << "No\n";
//         return;
//     }

//     ll t_size = size_diff / (x1 - y1);
//     if(t_size * (x1-y1) != size_diff) {
//         cout << "No\n";
//         return;
//     }

//     string t = "";
//     ll yp = 0, yi = 0;
//     while(x[yp] == y[yp]) {
//         yp++;
//     }

//     if(y[yp] == '1') {
//         swap(x,y);
//     }

//     for(ll i = 0; i < t_size; i++) {
//         if(y[yp] == '0') {
//             t.push_back(s[yi]);
//             yi++;
//             if(yi == s.size()) {
//                 yp++;
//                 yi = 0;
//             }
//         } else if(y[yp] == '1') {
//             t.push_back(t[yi]);
//             yi++;
//         }
//     }

//     // cout << "s : " << s << '\n';
//     // cout << "t : " << t << '\n';

//     ll ok = 1;
//     ll xp = 0, xi = 0;
//     yp = 0, yi = 0;

//     stringhash shs(s), sht(t);

//     ll cnt = 0;

//     while(xp != x.size() || yp != y.size()) {
//         cnt++;
//         ll x_left = (x[xp] == '0' ? s.size() : t.size()) - xi;
//         ll y_left = (y[yp] == '0' ? s.size() : t.size()) - yi;

//         ll len = min(x_left, y_left);

//         // cout << "xp : " << xp << " xi : " << xi << '\n';
//         // cout << "yp : " << yp << " yi : " << yi << '\n';
//         // cout << "len : " << len << '\n';

//         ll hx = (x[xp] == '0' ? shs.get_hash(xi, xi + len) : sht.get_hash(xi, xi + len));
//         ll hy = (y[yp] == '0' ? shs.get_hash(yi, yi + len) : sht.get_hash(yi, yi + len));

//         // cout << "hx : " << hx << " hy : " << hy << '\n';

//         if(hx != hy) {
//             ok = 0;
//         }

//         xi += len;
//         yi += len;

//         if(x[xp] == '0' && xi == s.size() || x[xp] == '1' && xi == t.size()) {
//             xp++;   
//             xi = 0;
//         }

//         if(y[yp] == '0' && yi == s.size() || y[yp] == '1' && yi == t.size()) {
//             yp++;
//             yi = 0;
//         }

//         assert(cnt < 2'000'000);

//     }

//     cout << (ok ? "Yes" : "No") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     buildsh();

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }