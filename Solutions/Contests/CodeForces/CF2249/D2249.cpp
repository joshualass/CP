#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
criss cross
4 0
0 1 2 3
1 0 3 2
2 3 0 1
3 2 1 0

4 1
0 2 1 3
2 1 3 0
1 3 0 2
3 0 2 1

*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void check(int n, vector<vector<int>> res, int x) {
    cout << "checking n : " << n << " x : " << x << endl;
    for(auto x : res) cout << x << endl;
    for(int i = 0; i < n; i++) {
        {
            auto z = res[i];
            sort(z.begin(), z.end());
            auto p = z;
            iota(p.begin(), p.end(), 0);
            assert(p == z);
            // cout << "i : " << i << " z : " << z << endl;
        }
        {
            vector<int> z;
            for(int j = 0; j < n; j++) {
                z.push_back(res[j][i]);
            }
            sort(z.begin(), z.end());
            auto p = z;
            iota(p.begin(), p.end(), 0);
            assert(p == z);
        }
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < n; j++) {
            int z = 0;
            for(int a = -1; a <= 0; a++) {
                for(int b = -1; b <= 0; b++) {
                    z ^= res[i + a][j + b];
                }
            }
            assert(z == x);
        }
    }
}

void solve(int n, int x) {

    vector<vector<int>> res(n, vector<int>(n));
    int ok = 1;

    if(n & 1) {
        ok = 0;
    } else if(n == 2 && x == 0) {
        res = {
            {0, 1},
            {1, 0}
        };
        // if(n % 2 == 0) {
        //     for(int i = 0; i * 2 < n; i++) {
        //         for(int j = 0; j * 2 < n; j++) {
        //             for(int k = 0; k < 2; k++) {
        //                 for(int l = 0; l < 2; l++) {
        //                     int d = (i + j) % (n / 2) * 2;
        //                     d += k == l;
        //                     res[i * 2 + k][j * 2 + l] = d;
        //                 }
        //             }
        //         }
        //     }
        // } else {
        //     ok = 0;
        // }
    } else if(__builtin_popcount(n) == 1 && (n != 2 || x != 1)) {

        int ln = 31 - __builtin_clz(n);
        // cout << "ln : " << ln << endl;
        for(int bit = ln - 1; bit >= 0; bit--) {
            for(int i = 0; i * 2 < n; i++) {
                for(int j = 0; j * 2 < n; j++) {
                    for(int k = 0; k < 2; k++) {
                        for(int l = 0; l < 2; l++) {
                            int b = 0;
                            for(int z = 1; z <= bit; z++) {
                                b ^= (i >> (z - 1)) & 1;
                                b ^= (j >> (z - 1)) & 1;
                            }
                            if((x >> bit) & 1) {
                                b ^= i & 1;
                                b ^= j & 1;
                                if(bit == 0) {
                                    b ^= k == 0 && l == 0;
                                } else {
                                    b ^= k == 1 && l == 1;
                                }
                            } else {
                                b ^= k & 1;
                                b ^= l & 1;
                                // if(bit == 0) {
                                //     b ^= ()
                                // }
                                // if(bit == 0 && ((x >> 1) & 1) == 0) {
                                //     b ^= (i & 1) == (j & 1);
                                // } else {
                                //     // b ^= i & 1;
                                //     // b ^= j & 1;
                                //     b ^= k != l;
                                // }
                            }
                            // cout << "bit : " << bit << " i : " << i << " j : " << j << " k : " << k << " l : " << l << " b : " << b << endl;
                            res[i * 2 + k][j * 2 + l] += b << bit;
                        }
                    }
                }
            }
        }

    } else {
        ok = 0;
    }

    if(ok) {
        check(n, res, x);
        for(int i = 0; i < n; i++) cout << res[i] << '\n';
    } else {
        cout << "-1\n";
    }

}

int debug = 1;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        int casi; cin >> casi;
        for(int i = 0; i < casi; i++) {
            int n, x; cin >> n >> x;
            solve(n, x);
        }
    } else {
        for(int n = 2; n <= 16; n++) {
            for(int x = 0; x < n; x++) {
                solve(n, x);
            }
        }
    }


    return 0;
}