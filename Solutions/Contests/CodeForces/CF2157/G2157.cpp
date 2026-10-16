#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());


ld gc = 0;
const int debug = 0;
// const int debug = 1;
const int N = 100;
vector<int> ha;

struct DS {

    int n;
    vector<int> par, s;
    DS(int n): n(n), par(n + 1), s(n + 1) {
        iota(par.begin(), par.end(), 0);
    }

    //returns {root, xor from i to this root}
    int find(int i) {
        if(par[i] != i) {
            int x = find(par[i]);
            s[i] ^= s[par[i]];
            par[i] = x;
        }
        return par[i];
    }

    int get(int l, int r) {
        int pl = find(l), pr = find(r);
        if(pl == pr) {
            return s[l] ^ s[r];
        } else {
            return -1;
        }
    }

    void merge(int l, int r, int x) {
        int pl = find(l), pr = find(r);
        if(pl == pr) {
            //assume the range is good. 
            assert(x == (s[l] ^ s[r]));
        } else {
            x ^= s[l];
            x ^= s[r];
            par[pr] = pl;
            s[pr] = x;
        }
    }
};

void solve() {
    
    int n; 
    if(debug == 0) {
        cin >> n;
    } else {
        n = N;
    }
    
    vector<DS> a;
    for(int i = 0; i < 30; i++) a.push_back(DS(n));

    ld c = 0;

    auto ask = [&](int l, int r) -> int {
        int res; 
        if(debug == 0) {
            cout << "? " << l + 1 << " " << r << endl;
            cin >> res;
        } else {
            res = 0;
            for(int i = l; i < r; i++) res ^= ha[i];
            res = 31 - __builtin_clz(res);
        }
        c += 1 / ((ld) (r - l));
        assert(res != -2);
        return res;
    };

    auto query = [&](int l, int r) -> int {
        for(int bit = 29; bit >= 0; bit--) {
            int q = a[bit].get(l, r);
            if(q == -1) {
                return -2;
            } else if(q == 0) {
                continue;
            } else {
                return bit;
                break;
            }
        }
        return -1;
    };

    for(int len = n; len >= 1; len--) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            if(query(l, r) == -2) {
                int res = ask(l, r);
                for(int bit = 29; bit >= max(0, res); bit--) {
                    if(bit == res) {
                        a[bit].merge(l, r, 1);
                    } else {
                        a[bit].merge(l, r, 0);
                    }
                }
            }
        }
    }

    if(debug == 0) {
        cout << "!" << endl;
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j <= n; j++) {
            int x = query(i, j);
            if(debug == 0) {
                cout << x << " ";
            } else {
                int res = 0;
                for(int k = i; k < j; k++) res ^= ha[k];
                res = 31 - __builtin_clz(res);
                assert(x == res);
            }
        }
        if(debug == 0) {
            cout << endl;
        }
    }

    if(debug == 1) {
        cout << "c : " << c << endl;
        gc += c;
    }

    // if(debug == 0) {
    //     cout << "!" << endl;
    //     for(int i = 0; i < n; i++) {
    //         for(int j = i + 1; j <= n; j++) {
    //             cout << query(i, j) << " ";
    //         }
    //         cout << endl;
    //     }
    // } else {
    //     cout << "c : " << c << endl;
    // }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ld coin_use = 0;
    // for(int i = 50; i <= 100; i++) coin_use += ((ld) 1) / i;
    // coin_use *= 2;
    // cout << fixed << setprecision(10) << coin_use << endl;

    if(debug == 0) {
        int casi; cin >> casi;
        while(casi-->0) solve();
    } else {

        int t = 30;
        for(int i = 0; i < t; i++) {
            int n = N;
            ha.resize(n);
            for(int j = 0; j < n; j++) ha[j] = rng() % (1 << 30);
            solve();
        }

        cout << "local done gc : " << gc << endl;

    }


    return 0;
}