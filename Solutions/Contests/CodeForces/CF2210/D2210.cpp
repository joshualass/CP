#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s, t; cin >> s >> t;
    auto gc = [](string s) -> array<int,2> {
        int res = 0;
        for(int i = 1; i < sz(s); i++) {
            res += s.substr(i-1,2) == ")(";
        }

        int l = 0, r = sz(s) / 2;
        while(l != r) {
            int m = (l + r + 1) / 2;
            int ok = 1;
            for(int i = 0; i < m; i++) {
                if(s[i] != '(') ok = 0;
                if(s[sz(s)-1-i] != ')') ok = 0;
            }
            int cur = 0;
            for(int i = m; i < sz(s) - m; i++) {
                if(s[i] == '(') cur++;
                else cur--;
                if(cur < 0) ok = 0;
            }
            if(ok) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        return {res, l};
    };
    cout << (gc(s) == gc(t) ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// /*

// (((()())))((()))
//    __     ______
// (((((()))())))()

// */

// mt19937 rng;

// bool isprime(ll num) {
//     if(num <= 1) return 0;
//     if(num == 2 || num == 3) return 1;
//     if(num % 2 == 0 || num % 3 == 0) return 0;
//     for(int i = 5; i <= sqrt(num); i++) {
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

// void buildsh() {
//     rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
//     M1 = gen_prime(900000000,1000000000);
//     B1 = gen_prime(9000,10000);
//     M2 = gen_prime(900000000,1000000000);
//     B2 = gen_prime(9000,10000);
// }

// void solve() {
    
//     int n; cin >> n;
//     string s, t; cin >> s >> t;

//     auto gh = [](string s) -> array<ll,2> {
//         stack<vector<array<ll,2>>> st;
//         st.push({});

//         auto vth = [&](vector<array<ll,2>> a) -> array<ll,2> {
//             a.push_back({1, 1});
//             sort(a.begin(), a.end());
//             array<ll,2> res = {629346, 23497};
//             ll mul1 = B1, mul2 = B2;
//             for(auto [h1, h2] : a) {
//                 res[0] = (res[0] + h1 * mul1) % M1;
//                 res[1] = (res[1] + h2 * mul2) % M2;
//                 mul1 = (mul1 * B1) % M1;
//                 mul2 = (mul2 * B2) % M1;
//             }
//             return res;
//         };

//         for(char c : s) {
//             if(c == '(') {
//                 st.push({});
//             }
//             if(c == ')') {
//                 auto a = st.top();
//                 st.pop();
//                 st.top().push_back(vth(a));
//             }
//         }
//         return vth(st.top());
//     };

//     cout << (gh(s) == gh(t) ? "YES" : "NO") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     buildsh();

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }