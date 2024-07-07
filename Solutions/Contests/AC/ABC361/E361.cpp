#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//find longest path in tree
ll res = 0;

void dfs1(int i, int p, vector<ll> &dp, vector<vector<array<ll,2>>> &adj) {
    ll m = 0;
    for(array<ll,2> c : adj[i]) {
        if(c[0] != p) {
            dfs1(c[0], i, dp, adj);
            m = max(m, dp[c[0]] + c[1]);
        }
    }
    dp[i] = m;
}

void dfs2(int i, int p, ll prev, vector<ll> &dp, vector<vector<array<ll,2>>> &adj) {

    vector<array<ll,2>> a;
    a.push_back({0,-1});

    res = max(res, prev);

    for(array<ll,2> c : adj[i]) {
        if(c[0] != p) {
            a.push_back({c[1] + dp[c[0]], c[0]});
        }
    }

    sort(a.begin(), a.end());

    for(array<ll,2> c : adj[i]) {
        if(c[0] != p) {
            for(int j = a.size() - 1; j >= 0; j--) {
                if(a[j][1] != c[0]) {
                    dfs2(c[0], i, max(prev, a[j][0]) + c[1], dp, adj);
                    break;
                }
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<array<ll,2>>> adj(n);
    ll shijak = 0;
    for(int i = 1; i < n; i++) {
        ll a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        shijak += c * 2;
    }
    
    vector<ll> dp(n);
    dfs1(0,-1,dp,adj);
    dfs2(0,-1,0,dp,adj);

    cout << shijak - res << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// //d1 stores the cost to visit the d1 subtree
// void dfs1(int i, int p, vector<ll> &d1, vector<vector<array<ll,2>>> &adj) {

//     ll score = 0;
//     for(array<ll,2> c : adj[i]) {
//         if(c[0] != p) {
//             dfs1(c[0],i,d1,adj);
//             score += c[1] * 2 + d1[c[0]];
//         }
//     }

//     d1[i] = score;

// }

// void dfs2(int i, int p, vector<ll> &d1, vector<vector<array<ll,2>>> &adj) {
    
//     for(array<ll,2> c : adj[i]) {
//         if(c[0] == p) {
//             d1[i] = d1[c[0]]
//         }
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     vector<vector<array<ll,2>>> adj(n);
//     for(int i = 1; i < n; i++) {
//         ll a, b, c; cin >> a >> b >> c;
//         a--; b--;
//         adj[a].push_back({b,c});
//         adj[b].push_back({a,c});
//     }

//     vector<ll> d1(n);
//     dfs1(0,-1,d1,adj);
//     dfs2(0,-1,d1,adj);

//     return 0;
// }