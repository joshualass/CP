#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 2e6;
int dsu[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    for(int i = 0; i < N; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }

    for(int i = 1; i < n; i++) {
        merge(9 * n, 9 * n + i);
    }

    int currscore = 10 * (n - 1);

    for(int i = 0; i < n - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--; c--;
        for(int level = 9; level >= c; level--) {
            if(find(level * n + a) != find(level * n + b)) currscore--;
            merge(level * n + a, level * n + b);
        }
    }   

    for(int i = 0; i < q; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--; w--;
        for(int level = 9; level >= w; level--) {
            if(find(level * n + u) != find(level * n + v)) currscore--;
            merge(level * n + u, level * n + v);
        }
        cout << currscore << '\n';
    }

    return 0;
}

/*

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int MAXN = 200000;
const int SN = 447;

//pref doesn't need MAXN elements. Just needs for each prefix, all the mods. therefore only SN^2

ll pref[SN][SN];
ll adds[200000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(pref,0,sizeof(pref));
    memset(adds,0,sizeof(adds));
    int n; cin >> n;

    ll res = 0;
    adds[0] = 1;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        ll curr = adds[i];
        for(int j = 1; j < SN; j++) {
            curr += pref[i%SN][j];
            if(curr >= MOD) curr -= MOD;
            if(j + i < n) {
                pref[(j + i)%j][j] += pref[i%j][j];
                if(pref[(j + i)%j][j] >= MOD) pref[(j + i)%j][j] -= MOD;
            }
        }
        if(num < SN) {
            if(num + i < n) {
                pref[(num + i)%num][num] += curr;
                if(pref[(num + i)%num][num] >= MOD) pref[(num + i)%num][num] -= MOD;
            }
        } else {
            for(ll j = 1; i + num * j < n; j++) {
                adds[i + num * j] += curr;
                if(adds[i + num * j] >= MOD) adds[i + num * j] -= MOD;
            }
        }
        res += curr;
        if(res >= MOD) res -= MOD;
    }
    cout << res << '\n';

    return 0;
}

// ll pref[200000][SN];
// ll adds[200000];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     memset(pref,0,sizeof(pref));
//     memset(adds,0,sizeof(adds));
//     int n; cin >> n;

//     ll res = 0;
//     adds[0] = 1;
//     for(int i = 0; i < n; i++) {
//         ll num; cin >> num;
//         ll curr = adds[i];
//         for(int j = 1; j < SN; j++) {
//             curr += pref[i][j];
//             if(curr >= MOD) curr -= MOD;
//             if(j + i < n) {
//                 pref[j + i][j] += pref[i][j];
//                 if(pref[j + i][j] >= MOD) pref[j + i][j] -= MOD;
//             }
//         }
//         if(num < SN) {
//             if(num + i < n) {
//                 pref[num + i][num] += curr;
//                 if(pref[num + i][num] >= MOD) pref[num + i][num] -= MOD;
//             }
//         } else {
//             for(ll j = 1; i + num * j < n; j++) {
//                 adds[i + num * j] += curr;
//                 if(adds[i + num * j] >= MOD) adds[i + num * j] -= MOD;
//             }
//         }
//         res += curr;
//         if(res >= MOD) res -= MOD;
//     }
//     cout << res << '\n';

//     return 0;
// }

*/