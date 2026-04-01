#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
binary lifting? no
treap? no
dsu? ok

ok. just observe that all numbers are a subset of the root value bro / can't have any gcd larger than a[i] lol. impossible observation !
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const int N = 2e5;
int dsu[N];
ll g[N];

void dsubuild(int n = N) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
    }
}

array<ll,2> find(int x) {
    if(dsu[x] == x) {
        return array<ll,2>{x, g[x]};
    }
    auto [ch, chg] = find(dsu[x]);
    dsu[x] = ch;
    g[x] = gcd(g[x], chg);
    return array<ll,2>{dsu[x], g[x]};
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> ch(n);
    vector<int> r(n);

    dsubuild(n);

    for(int i = n - 1; i >= 0; i--) {
        ll k; cin >> g[i] >> k;
        vector<int> cc(k);
        for(int &c : cc) {
            cin >> c;
            c--;
            dsu[c] = i;
            r[i] += r[c];
        }

        // cout << "i : " << i << " cc : " << cc << endl;

        int f = 0;
        for(int c : cc) {
            while(sz(ch[c]) && f == 0) {
                int x = ch[c].back();
                auto [par, gpath] = find(x);
                if(gpath == 1) {
                    ch[c].pop_back();
                } else { 
                    f = 1;
                }
            }
            if(f) break;
        }
        if(f) {
            int mx = cc[0];
            for(int c : cc) {
                if(sz(ch[c]) > sz(ch[mx])) mx = c;
            }
            swap(ch[i], ch[mx]);
            for(int c : cc) {
                if(c != mx) {
                    for(int x : ch[c]) ch[i].push_back(x);
                    ch[c].clear();
                }
            }
        } else {
            r[i]++;
            ch[i].push_back(i);
        }
        cout << r[i] << endl;
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
// #define sz(x) (ll) (x).size()

// void solve() {
    
//     ll n; cin >> n;
//     vector<vector<ll>> cand(n), cand_lazy(n);
//     vector<ll> a(n), lazy_g(n);
//     vector<ll> s(n);

//     for(ll i = n - 1; i >= 0; i--) {
//         cin >> a[i];
//         ll k; cin >> k;
//         vector<ll> ch(k);
//         for(ll &x : ch) {
//             cin >> x;
//             x--;
//             s[i] += s[x];
//         }

//         ll f = 0;
//         for(ll j = 0; j < k && f == 0; j++) {
//             ll c = ch[j];
//             while(sz(cand[c]) && f == 0) {
//                 if(gcd(a[i], cand[c].back()) == 1) {
//                     cand[c].pop_back();
//                 } else {
//                     f = 1;
//                 }
//             }
//             while(sz(cand_lazy[c]) && f == 0) {
//                 if(gcd(a[i], gcd(cand_lazy[c].back(), lazy_g[c])) == 1) {
//                     cand_lazy[c].pop_back();
//                 } else {
//                     f = 1;
//                 }
//             }
//         }

//         if(f) {
//             assert(k);
//             ll mx = 0;
//             for(ll j = 1; j < k; j++) {
//                 ll c = ch[j];
//                 if(sz(cand_lazy[c]) > sz(cand_lazy[mx])) {
//                     mx = j;
//                 }
//             }

//             ll cs = 0;
//             for(ll j = 0; j < k; j++) {
//                 cs += sz(cand[ch[j]]);
//             }

//             if(cs > sz(cand_lazy[mx])) {
//                 lazy_g[i] = a[i];
//                 ll mxc = 0;
//                 for(ll j = 1; j < k; j++) {
//                     ll c = ch[j];
//                     if(sz(cand[c]) > sz(cand[mxc])) {
//                         mxc = j;
//                     }
//                 }
//                 swap(cand_lazy[i], cand[ch[mxc]]);
//                 for(ll j = 0; j < k; j++) {
//                     ll c = ch[j];
//                     if(j != mxc) {
//                         for(ll x : cand[c]) {
//                             if(x != 1) {
//                                 cand_lazy[i].push_back(x);
//                             }
//                         }
//                     }
//                     for(ll x : cand_lazy[c]) {
//                         ll t = gcd(x, lazy_g[c]);
//                         if(t != 1) {
//                             cand_lazy[i].push_back(t);
//                         }
//                     }
//                 }
//             } else {
//                 lazy_g[i] = gcd(a[i], lazy_g[ch[mx]]);
//                 swap(cand_lazy[i], cand_lazy[ch[mx]]);
//                 for(int j = 0; j < k; j++) {
//                     int c = ch[j];
//                     if(j != mx) {
//                         for(ll x : cand_lazy[c]) {
//                             ll t = gcd(a[i], gcd(x, lazy_g[c]));
//                             if(t != 1) {
//                                 cand[i].push_back(t);
//                             }
//                         }
//                     }
//                     for(ll x : cand[c]) {
//                         ll t = gcd(x, a[i]);
//                         if(t != 1) {
//                             cand[i].push_back(t);
//                         }
//                     }
//                 }
//             }
//         } else {
//             s[i]++;
//             cand[i].push_back(a[i]);
//         }
//         cout << s[i] << endl;
//         for(ll c : ch) {
//             cand_lazy[c].clear();
//             cand[c].clear();
//         }
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }