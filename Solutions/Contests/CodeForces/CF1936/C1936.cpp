#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//new year, new attempt :)

/*
need to do the following to get it to work
for the priority queue, add to the queue the minimal cost to get a pokemon before paying its c_i as well as with it's c_i. 
this avoids some bottleneck stuff. 
probably best practice to optimize the dijkstra. 
*/

void solve() {
    
    int n, m; cin >> n >> m;
    
    vector<ll> c(n);
    for(ll &x : c) cin >> x;
    vector<vector<array<ll,2>>> a(m, vector<array<ll,2>>(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x; cin >> x;
            x *= -1;
            a[j][i] = {x, i};
        }
    }

    vector<vector<int>> reva(m, vector<int>(n));
    for(int i = 0; i < m; i++) {
        sort(a[i].begin(), a[i].end());
        for(int j = 0; j < n; j++) {
            reva[i][a[i][j][1]] = j;
        }    
    }

    vector<vector<ll>> vis(n, vector<ll>(m, -1));
    vector<ll> b(n, -1);

    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;

    pq.push({0, 0});

    while(pq.size()) {
        vector<ll> cur = pq.top();
        pq.pop();
        ll cost = cur[0], i = cur[1];
        if(cur.size() == 2) {
            if(b[i] != -1) continue;
            b[i] = cost;

            // cout << "at i : " << i << " cost : " << cost << '\n';

            if(i == n - 1) {
                cout << cost << '\n';
                break;
            }

            for(int j = 0; j < m; j++) {
                int idx = reva[j][i];
                if(idx) {
                    pq.push({cost, a[j][idx - 1][1], j});
                }
                if(idx + 1 < n) {
                    pq.push({cost + a[j][idx + 1][0] - a[j][idx][0], a[j][idx + 1][1], j});
                }
            }

        } else {
            ll attr = cur[2];
            if(vis[i][attr] != -1) continue;
            vis[i][attr] = cost;

            // cout << "pre i : " << i << " attr : " << attr << " cost : " << cost << '\n';
            
            pq.push({cost + c[i], i}); 
            
            int idx = reva[attr][i];
            if(idx) {
                pq.push({cost, a[attr][idx - 1][1], attr});
            }
            if(idx + 1 < n) {
                pq.push({cost + a[attr][idx + 1][0] - a[attr][idx][0], a[attr][idx + 1][1], attr});
            }
        }
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
// const ll MOD = 998244353;

// /*

// read the editorial a while ago, but didn't understand what was happening.

// thought about and idea arrived later. Editorial solution is not something I would come up with independently.
// always nice to look at problem later

// */

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {

//     ll n, m; cin >> n >> m;

//     vector<vector<ll>> ar(n,vector<ll>(m)); //i - pokemon, j - attribute, store -> what rank in r. 
//     vector<vector<ll>> avis(n,vector<ll>(m)); //i - pokemon, j - attribute, store -> if visited this pokemon for this attribute
//     vector<vector<array<ll,2>>> r(m,vector<array<ll,2>>(n)); //i - attribute, j - rank, k - {attribute, pokemon at rank j}
//     vector<map<ll,vector<ll>>> scores(m);
//     vector<ll> costs(n); //cost of pokemon at index i
//     vector<map<ll,ll>> minats(m); 

//     for(ll &x : costs) cin >> x;

//     for(ll i = 0; i < n; i++) {
//         for(ll j = 0; j < m; j++) {
//             cin >> r[j][i][0];
//             r[j][i][1] = i;

//             scores[j][r[j][i][0] - costs[i]].push_back(i);

//         }
//     }

//     for(ll i = 0; i < m; i++) {
//         sort(r[i].rbegin(), r[i].rend());
//         for(ll j = 0; j < n; j++) {
//             ar[r[i][j][1]][i] = j;
//         }
//     }

//     vector<ll> vis(n,-1);

//     priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq; 
//     pq.push({0,0});

//     // need to maintain that when we visit an element, it is the next element with lowest cost. 
//     while(pq.size()) {
//         auto [cost, i] = pq.top();
//         pq.pop();

//         if(vis[i] != -1) continue;
//         vis[i] = cost;

//         cout << "i : " << i << " cost : " << cost << '\n';

//         for(ll j = 0; j < m; j++) {
//             //add all pokemon with greater attribute that haven't already been added. 
//             int irank = ar[i][j];
//             int iattribute = r[j][irank][0];

//             for(ll k = irank; k >= 0; k--) {
//                 auto [attribute, pokemon] = r[j][k];
//                 if(avis[pokemon][j]) break;
//                 avis[pokemon][j] = 1;
//                 ll nc = cost + costs[pokemon];
//                 pq.push({nc, pokemon});
//             }
//             // add all pokemon with same level of attribute that haven't already been added. 
//             for(ll k = irank + 1; k < n; k++) {
//                 if(r[j][k][0] == iattribute) {
//                     auto [attribute, pokemon] = r[j][k];
//                     if(avis[pokemon][j]) break;
//                     avis[pokemon][j] = 1;
//                     ll nc = cost + costs[pokemon];
//                     pq.push({nc, pokemon});
//                 } else {
//                     break;
//                 }
//             }



//             if(minats[j].lower_bound(cost) != minats[j].end() && )



//             minat[j] = min(minat[j], cost + r[j][ar[i][j]][0]);

//             if(scores[j].lower_bound())

//             if(acr[i][j] != n - 1) { //next one should be next lowest cost. 
//                 auto [nextattribute, nextpokemon] = rc[j][acr[i][j] + 1];

//                 cout << "i : " << i << " j : " << j << " na : " << nextattribute << " np : " << nextpokemon << '\n';

//                 cout << "i : " << i << " pushnext : " << minat[j] - nextattribute + costs[nextpokemon] << " who : " << nextpokemon << '\n';
//                 cout << "comps of calc minato : " << minat[j] << " na : " << nextattribute << " cost : " << costs[nextpokemon] << '\n';

//                 pq.push({minat[j] - nextattribute + costs[nextpokemon], nextpokemon});
//             }
//         }
//     }

//     // cout << "allvis : " << vis << '\n';

//     cout << vis[n-1] << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }