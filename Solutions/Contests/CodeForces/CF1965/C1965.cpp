#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int lo = 0, hi = 1;
    int curr = hi;
    bool forward = 1;
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i-1]) forward ^= 1;
        if(forward) {
            curr++;
            hi = max(hi,curr);
        } else {
            curr--;
            lo = min(lo,curr);
        }
    }
    cout << hi - lo << '\n';
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
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// vector<int> manacher_odd(string s) {
//     int n = s.size();
//     s = "$" + s + "^";
//     vector<int> p(n + 2);
//     int l = 1, r = 1;
//     for(int i = 1; i <= n; i++) {
//         p[i] = max(0, min(r - i, p[l + (r - i)]));
//         while(s[i - p[i]] == s[i + p[i]]) {
//             p[i]++;
//         }
//         if(i + p[i] > r) {
//             l = i - p[i], r = i + p[i];
//         }
//     }
//     return vector<int>(begin(p) + 1, end(p) - 1);
// }

// vector<int> manacher(string s) {
//     string t;
//     for(auto c: s) {
//         t += string("#") + c;
//     }
//     auto res = manacher_odd(t + "#");
//     return vector<int>(begin(res) + 1, end(res) - 1);
// }

// void solve() {

//     int n; cin >> n;

//     string s; cin >> s;

//     set<pair<int,int>> pals; //{length, index}

//     vector<int> man = manacher(s);

//     cout << man << '\n';

//     vector<set<pair<int,int>>> kill(n); //length idx
//     for(int i = 1; i < n; i++) {
//         int length = man[i * 2 - 1] / 2;
//         set<pair<int,int>>::iterator it;
//         bool found = 0;
//         while(1) {
//             found = 0;
//             it = pals.upper_bound({length + 1, -1});
//             if(it != pals.begin()) {
//                 it--;
//                 if((*it).first + (*it).second < i) {
//                     pals.erase(it);
//                     continue;
//                 }
//                 found = 1;
//             }
//             break;
//         }
//         if(found) {
//             int length = (*it).first;
//             cout << "i : " << i << " length : " << length << '\n';
//             kill[i - length * 2].insert({length, i});
//         }
//         pals.insert({length,i});
//     }

//     // string res = "";
//     // int active = -1;
//     // for(int i = 0; i < n; i++) {
//     //     if(i == active) active = -1;
//     //     if(active == -1 && kill[i].size()) {
//     //         active = (*--kill[i].end()).second;
//     //     }
//     //     if(active == -1) {
//     //         res.push_back(s[i]);
//     //     }
//     // }

//     // cout << "res : " << res << '\n';


// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// const ll M1 = 998244353, B1 = 9973;
// const ll M2 = 1e9 + 9, B2 = 9931;
// struct stringhash {
//     vector<ll> h1, h2;
//     vector<ll> p1, p2;
//     int n;

//     stringhash(string s) {
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

// void solve() {
//     int n; cin >> n;
//     string s; cin >> s;

//     string a = "";
//     for(int i = 0; i < n; i++) {
//         a.push_back(s[i]);
//         if(a.size() >= 3 && a[a.size() - 3] == a[a.size() - 2] && a[a.size() - 2] == a[a.size() - 1]) {
//             a.pop_back();
//             a.pop_back();
//         }
//     }

//     //remove ends 

//     stringhash sh(a);
//     string rev = a;
//     reverse(rev.begin(), rev.end());
//     stringhash shrev(rev);
//     for(int lo = a.size() - 1; lo >= 0; lo--) {
//         int lb = lo - (a.size() - lo);
//         if(sh.get_hash(lb,lo) == shrev.get_hash(n - a.size(),n - lo)) {
//             while(a.size() != lo) a.pop_back();
//         }
//     }
//     cout << "in between a : " << a << '\n';
//     reverse(a.begin(), a.end());
//     stringhash sh2(a);
//     rev = a;
//     reverse(rev.begin(), rev.end());
//     stringhash shrev2(rev);
//     n = a.size();
//     for(int lo = a.size() - 1; lo >= 0; lo--) {
//         int lb = lo - (a.size() - lo);
//         if(sh2.get_hash(lb,lo) == shrev2.get_hash(n - a.size(),n - lo)) {
//             for(int j = 0; j < a.size() - lo; j++) {
//                 a.pop_back();
//             }
//         }
//     }
//     cout << "final a : " << a << '\n';
//     cout << a.size() << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }