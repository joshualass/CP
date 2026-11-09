#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;

    // if(n == 1){
    //     cout << "0\n";
    // }else if(n == 2){
    //     cout << "0 1 3 2\n";
    // }else{
    //     vector<ll> curr;
    //     vector<ll> ps = {0,1,2,5,3,11,6,13,4,10,7,9,14,12,8};
    //     // for(int j = 2; j < n; j++){
    //     //     vector<ll> nex;
    //     //     for(int i = 1; i < curr.size(); i++){
    //     //         nex.push_back((1 << j) + curr[i]);
    //     //     }
    //     //     nex.push_back((1 << j));
    //     //     vector<ll> final;
    //     //     ll side = 1;
    //     //     for(int i = 0; i < (1 << j); i++){
    //     //         if(i % 2 == 0){
    //     //             side ^= 1;
    //     //         }
    //     //         if(side == 0){
    //     //             final.push_back(curr[i]);
    //     //         }else{
    //     //             final.push_back(nex[i]);
    //     //         }
    //     //     }
    //     //     side = 1;
    //     //     for(int i = (1 << j) - 1; i >= 0; i--){
    //     //         if(i % 2 == 1){
    //     //             side ^= 1;
    //     //         }
    //     //         if(side == 0){
    //     //             final.push_back(curr[i]);
    //     //         }else{
    //     //             final.push_back(nex[i]);
    //     //         }
    //     //     }
    //     //     swap(final, curr);
    //     // }
    //     // set<ll> stuff;
    //     for(int i = 0; i < ps.size(); i++){
    //         // cout << curr[i] << " ";
    //         if(i != 0){
    //             cout << (ps[i] ^ ps[i - 1]) << ' ';
    //             // stuff.insert(curr[i] ^ curr[i - 1]);
    //         }
    //     }
    //     // cout << "\n";
    //     // cout << stuff.size() << "\n";
    // }

    ll len = 1 << n;

    // for(ll i = 0; i < 1LL << len; i++) {
    //     // cout << "i : " << i << endl;
    //     if(__builtin_popcount(i) == len / 2) {
    //         vector<ll> a(len);
    //         for(ll j = 0; j < len; j++) {
    //             a[j] = ((i >> j) & 1) << (n - 1);
    //         }
    //         for(ll j = 0; j < len; j++) {
    //             if(a[j]) {
    //                 for(ll k = 1; k < n; k++) {
    //                     if(j - k < 0) {
    //                         break;
    //                     }
    //                     a[j - k] += 1 << (n - 1 - k);
    //                 }
    //             }
    //         }
    //         // cout << "i : " << i << " a : " << a << endl;
    //         set<ll> s(a.begin(), a.end());
    //         if(sz(s) == len) {
    //             vector<ll> vis(len);
    //             vector<ll> p(len);
    //             ll cur = 0;
    //             for(int j = 0; j < len; j++) {
    //                 ll x = a[j];
    //                 cur ^= x;
    //                 vis[cur] = 1;
    //                 if(j) p[j] ^= p[j-1];
    //                 p[j] ^= x;
    //             }
    //             vis.pop_back();
    //             if(accumulate(vis.begin(), vis.end(), 0) == len - 1) {
    //                 cout << bitset<16>{i} << endl;
    //                 cout << "a : " << a << endl;
    //                 cout << "p : " << p << endl;
    //             }
    //         }
    //     }
    // }

    // vector<ll> a(len);
    // vector<int> vis(len), vis2(len);

    // int cur = 0;
    // for(int i = 0; i < len; i++) {
    //     int f = -1;
    //     for(int j = len - 1; j >= 0; j--) {
    //         if(vis[j] == 0 && vis2[cur ^ j] == 0) {
    //             f = j;
    //             vis[j] = 1;
    //             cur ^= j;
    //             vis2[cur] = 1;
    //             break;
    //         }
    //     }
    //     a[i] = f;
    // }

    // cout << a << endl;

    vector<int> a(len);
    iota(a.begin(), a.end(), 1);
    a.back() = 0;
    while(1) {

        // cout << "a : " << a << endl;

        vector<ll> vis(len);
        vector<ll> p(len);
        ll cur = 0;
        for(int j = 0; j < len; j++) {
            ll x = a[j];
            cur ^= x;
            // if(j + 1 < len) {
                vis[cur] = 1;
            // }
            if(j) p[j] ^= p[j-1];
            p[j] ^= x;
        }
        vis.pop_back();
        int ok = 1;

        // for(int i = 0; i < len; i++) {
            // if(i % 4 == 1 || i % 4 == 2) {
            //     if(a[i] <= 3) ok = 0;
            // } else {
            //     if(a[i] >= 4) ok = 0;
            // }
        // }

        if(a[0] % 4 != 2) ok = 0;
        if(a[1] % 4 != 3) ok = 0;

        if(accumulate(vis.begin(), vis.end(), 0) == len - 1 && ok) {
            // cout << bitset<16>{i} << endl;
            cout << "a : " << a << endl;
            cout << "p : " << p << endl;
        }

        if(!next_permutation(a.begin(), a.end() - 1)) break;
    }

    return 0;
}

/*



*/