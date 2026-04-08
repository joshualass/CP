#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

//guessology ... 

/*

5 9 3 7 1 5 1 5 4 3
0 10 4 8 2 6 1 5 4 3
0 10 0 9 3 7 2 5 4 3
0 10 0 9 0 8 3 6 4 3
0 X 0 X 0 X X X X _
ok


0 X 4 8 2 6 1 5 4 3
0 X 0 9 3 7 2 5 4 3
0 X 0 X

5 2 0 5 5
5 2 0 5 0
0 3 1 6 1
0 3 1 0 2
0 3 0 1 2
0 0 1 2 3


*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve_slow(vector<int> a) {
    int n = sz(a);
    // int res = 0, bm = -1;
    // for(int i = 0; i < 1 << n; i++) {
    //     vector<int> b = a;
    //     for(int j = 0; j < n; j++) {
    //         if((i >> j) & 1) {

    //         } else {
    //             b[j] = 0;
    //             for(int k = 1; k <= b[j] && j + k < n; k++) {
    //                 b[j+k]++;
    //             }
    //         }
    //     }
    //     int cur = 1;
    //     for(int j = 0; j + 1 < n; j++) {
    //         if((i >> j) & 1) {
    //             if(j + b[j] >= n - 1) {
    //                 cur++;
    //             } else {
    //                 cur = -1e9;
    //             }
    //         }
    //     }
    //     if(cur > res) {
    //         res = cur;
    //         bm = i;
    //     }
    // }

    // cout << "res : " << res << endl;
    // cout << "bm : " << bm << endl;

    int res = 0;
    vector<int> bp;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    while(1) {  
        vector<int> b = a;
        for(int i : p) {
            for(int j = 1; j <= b[i] && i + j < n; j++) {
                b[i + j]++;
            }
            b[i] = 0;
        }
        if(is_sorted(b.begin(), b.end())) {
            int mex = 0;
            for(int x : b) {
                if(mex == x) mex++;
            }
            if(mex > res) {
                res = mex;
                bp = p;
            }
        }

        if(!next_permutation(p.begin(), p.end())) break;
    }
    
    cout << res << endl;
    cout << "p : " << bp << endl;

}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    // vector<int> k;
    // k.push_back(-1);
    // vector<int> p(n);
    // int cur = 0;
    // for(int i = 0; i < n; i++) {
    //     cur += p[i];
    //     if(a[i] + cur + i >= n - 1) {
    //         k.push_back(i);
    //     }
    //     cur++;
    //     if(a[i] + cur + 1 < n) {
    //         p[a[i] + cur + 1]--;
    //     }
    // }

    // auto simulate = [&](int r) -> int {
    //     // cout << "r : " << r << endl;
    //     int res = 1;
    //     p.assign(n, 0);
    //     cur = 0;
    //     for(int i = 0; i + 1 < n; i++) {
    //         cur += p[i];
    //         // cout << "i : " << i << " cur : " << cur << " p : " << p << endl;
    //         if(i + a[i] + cur >= n - 1 && i > r) {
    //             res++;
    //             // cout << "bink!" << endl;
    //         } else {
    //             cur++;
    //             // cout << "bonk :(" << endl;
    //             if(i + a[i] + cur + 1 < n) {
    //                 p[i + a[i] + cur + 1]--;
    //             }
    //         }
    //     }
    //     // cout << "sim res : " << res << endl;
    //     return res;
    // };

    // // int l = 0, r = sz(k) - 1;
    // // while(l != r) {
    // //     int m = (l + r + 1) / 2;
    // //     // cout << "l : " << l << " r : " << r << " m : " << m << endl;
    // //     if(simulate(k[m] - 1) <= simulate(k[m])) {
    // //         l = m;
    // //     } else {
    // //         r = m - 1;
    // //     }
    // // }

    // // cout << simulate(l) << '\n';

    // int res = 0;
    // for(int x : k) res = max(res, simulate(x));
    // cout << res << '\n';

    ll s = 0;
    for(int i = 0; i < n; i++) s += min(n - i - 1, a[i]);
    ll res = 1;
    while(res * (res + 1) / 2 <= s) res++;

    cout << res << '\n';

    cout << "slow" << endl;
    solve_slow(a);

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}