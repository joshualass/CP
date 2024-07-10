#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//oops q logn logn logn bad :( need -> q logn logn
//solution, we can do some precomputing to make queries faster
//good idea to analyze big O sooner vs later :)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

const int MAXN = 200000;

int lifts[MAXN][18];
int liftsor[MAXN][18];
int depths[MAXN];
int a[MAXN];

void dfs(int i, int p, int d, vector<vector<int>> &adj) {
    lifts[i][0] = p;
    liftsor[i][0] = a[i];
    if(p != -1) {
        liftsor[i][0] |= a[p];
    }
    depths[i] = d;

    for(int c : adj[i]) {
        if(c != p) {
            dfs(c,i,d+1,adj);
        }
    }
}

int findlca(int x, int y) {

    // cout << "lca x : " << x << " y : " << y << '\n';

    if(depths[y] > depths[x]) swap(x,y);

    for(int i = 17; i >= 0; i--) {
        if(depths[x] - (1 << i) >= depths[y]) {
            x = lifts[x][i];
        }
    }

    // cout << "p1 : " << x << " " << y << '\n';

    for(int i = 17; i >= 0; i--) {
        if(lifts[x][i] != lifts[y][i]) {
            x = lifts[x][i];
            y = lifts[y][i];
        }
    }

    // cout << "p2 : " << x << " " << y << '\n';

    if(x != y) {
        return lifts[x][0];
    } else {
        return x;
    }

}

int getpathor(int x, int y, int lca, int d) {

    if(d == 0) return 0;

    int res = a[x];
    d--;

    for(int i = 17; i >= 0; i--) {
        if(d >= (1 << i) && depths[x] - (1 << i) >= depths[lca]) {
            d -= (1 << i);
            res |= liftsor[x][i];
            x = lifts[x][i];
        }
    }

    // cout << "move x done res : " << res << " x : " << x << " y : " << y << " lca : " << lca << " d : " << d << '\n';

    if(d) {

        int dist = depths[y] - depths[lca];

        int up = dist - d;
        for(int i = 17; i >= 0; i--) {
            if(up >= (1 << i)) {
                up -= 1 << i;
                y = lifts[y][i];
            }
        }

        for(int i = 17; i >= 0; i--) {
            if(d >= (1 << i)) {
                d -= 1 << i;
                res |= liftsor[y][i];
                y = lifts[y][i];
            }
        }
    }

    return res;
}

int getpathorfaster(int x, int y, int lca, int d) {

    if(d == 0) return 0;

    int res = a[x];
    d--;

    int dist = depths[y] - depths[lca];

    int up = dist - d;
    for(int i = 17; i >= 0; i--) {
        if(up >= (1 << i)) {
            up -= 1 << i;
            y = lifts[y][i];
        }
    }

    for(int i = 17; i >= 0; i--) {
        if(d >= (1 << i)) {
            d -= 1 << i;
            res |= liftsor[y][i];
            y = lifts[y][i];
        }
    }

    return res;

}

void solve() {
    int n; cin >> n;

    for(int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0,-1,0,adj);

    // for(int i = 0; i < n; i++) {
    //     cout << "di : " << depths[i] << '\n';
    // }


    for(int d = 1; d < 18; d++) {
        for(int i = 0; i < n; i++) {
            int m = lifts[i][d-1];
            if(m != -1) {
                lifts[i][d] = lifts[m][d-1];
                liftsor[i][d] = liftsor[i][d-1] | liftsor[m][d-1];
            } else {
                lifts[i][d] = lifts[i][d-1];
                liftsor[i][d] = liftsor[i][d-1];
            }
        }
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        if(depths[x] < depths[y]) swap(x,y);
        int lca = findlca(x,y);
        int totald = depths[x] + depths[y] - depths[lca] * 2 + 1;
        int to_lca = getpathor(x,lca,lca,depths[x] - depths[lca] + 1);
        // cout << "i : " << i << " x : " << x << " y : " << y << " lca : " << lca << " td : " << totald << '\n';
        int res = 0;
        pb_map<int,int> NEEDMORESPEED;
        for(int pc = 1; pc < 30; pc++) {
            int l = 1, r = totald;
            while(l != r) {
                int m = (l + r) / 2;
                if(NEEDMORESPEED.find(m) == NEEDMORESPEED.end()) {
                    if(m >= depths[x] - depths[lca] + 1) {
                        NEEDMORESPEED[m] = __builtin_popcount(to_lca | getpathorfaster(lca,y,lca,m-(depths[x]-depths[lca])));
                    } else {
                        NEEDMORESPEED[m] = __builtin_popcount(getpathor(x,y,lca,m));
                    }
                }
                
                if( NEEDMORESPEED[m] >= pc) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            // cout << "i : " << i << " x : " << x << " y : " << y << " lca : " << lca << " l : " << l << '\n';
            // cout << "pc : " << pc << " l : " << l << '\n';
            // cout << "lhs : " << __builtin_popcount(getpathor(x,y,lca,l)) << '\n';
            // cout << "rhs : " << __builtin_popcount(getpathor(y,x,lca,totald - l + 1)) << '\n';
            res = max(res, __builtin_popcount(getpathor(x,y,lca,l)) + __builtin_popcount(getpathor(y,x,lca,totald - l + 1)));
        }
        cout << res << " \n"[i == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}