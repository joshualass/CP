#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ttfang

const int MAXN = 250000;
const int SN = 500; //nice
const int MOD = 998244353;

int a[SN][MAXN];
int bm[SN], cnts[MAXN][SN], tc[SN], b[MAXN]; //block mults, cnt of pref numbers, total count of elements in range, array values
vector<array<int,3>> queries[SN][MAXN];
int res[MAXN];
int fact[MAXN + 1], inv_fact[MAXN + 1], inv[MAXN + 1];

constexpr int power(int a, int b) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % MOD) {
        if (b % 2) {
            res = 1LL * res * a % MOD;
        }
    }
    return res;
}

int choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n-k] % MOD;
}

void init_fact(int n = MAXN) {
    fact[0] = 1;
    inv_fact[0] = 1;
    inv[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = 1LL * fact[i-1] * i % MOD;
    }
    inv_fact[n] = power(fact[n], MOD - 2);
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = 1LL * inv_fact[i+1] * (i + 1) % MOD;
    }
    for(int i = 1; i <= n; i++) {
        inv[i] = 1LL * inv_fact[i] * fact[i-1] % MOD;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i / SN][x]++;
        b[i] = x;
    }

    for(int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        l--, x--;
        queries[l / SN][x].push_back({l, r, i});
    }

    for(int i = 0; i < SN; i++) {
        //reset bm
        for(int j = 0; j < SN; j++) {
            bm[j] = 1;
        }
        
        for(int j = 0; j < MAXN; j++) {
            //add things
            int c = 0;
            for(int k = i + 1; k < SN; k++) {
                c += a[k][j];
                if(c) {
                    bm[k] = 1LL * bm[k] * inv_fact[c];
                }
                cnts[]
            }

            //query things

        }


    }

    return 0;
}
