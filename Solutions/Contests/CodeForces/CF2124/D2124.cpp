#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> b = a;
    sort(b.begin(), b.end());
    int kp = b[k - 1];
    vector<int> c;
    for(int x : a) if(x <= kp) c.push_back(x);

    // cout << "kp : " << kp << '\n';
    // cout << "c : " << c << '\n';

    int l = 0, r = c.size() - 1;
    int len = 0;
    while(l < c.size() && r >= 0) {
        // cout << "l : " << l << " r : " << r << " len : " << len << '\n';
        if(c[l] == c[r]) {
            l++;
            r--;
            len++;
        } else if(c[l] == kp) {
            l++;
        } else if(c[r] == kp) {
            r--;
        } else {
            cout << "NO\n";
            return;
        }
    }

    // cout << "final len : " << len << '\n';

    if(len + 1 >= k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

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

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

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
// struct stringhash {
//     vector<ll> h1, h2;
//     vector<ll> p1, p2;
//     int n;

//     stringhash(vector<int> s) {
//         this->n = s.size();
//         p1.push_back(1);
//         for(int i = 0 ; i < n; i++) {
//             p1.push_back(p1.back() * B1 % M1);
//         }
//         p2.push_back(1);
//         for(int i = 0 ; i < n; i++) {
//             p2.push_back(p2.back() * B2 % M2);
//         }
//         h1.push_back(0);
//         for(int i = 0; i < n; i++) {
//             h1.push_back((h1[i] * B1 + s[i]) % M1);
//         }
//         h2.push_back(0);
//         for(int i = 0; i < n; i++) {
//             h2.push_back((h2[i] * B2 + s[i]) % M2);
//         }
//     }

//     ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
//         ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
//         ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
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
    
//     int n, k; cin >> n >> k;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<int> b = a;
//     sort(b.begin(), b.end());
//     int kl = b[n - k];
//     vector<int> c;
//     for(int x : a) if(x >= kl) c.push_back(x);

//     cout << "c : " << c << '\n';

//     // stringhash fwsh(c);
//     // reverse(c.begin(), c.end());

//     int l = 0, r = c.size() - 1;

//     for(; l < c.size(); l++, r--) {
//         if(c[l] != c[r]) break;
//     }



//     cout << "l : " << l << " r : " << r << '\n';

//     if(l == c.size()) {
//         cout << "YES\n";
//         return;
//     }


//     auto check_pal = [](vector<int> a) -> int {
//         vector<int> b = a;
//         reverse(b.begin(), b.end());
//         return a == b;
//     };

//     vector<int> al = c, ar = c;
//     al.erase(al.begin() + l);
//     ar.erase(ar.begin() + r);

//     if(check_pal(al) || check_pal(ar)) {
//         cout << "YES\n";
//     } else {
//         cout << "NO\n";
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     buildsh();

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }