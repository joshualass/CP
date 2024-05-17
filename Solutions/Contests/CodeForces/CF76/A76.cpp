// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// const int N = 2e5;
// int dsu[N];
// int sizes[N];

// int find(int x) {
//     if(dsu[x] == x) {
//         return x;
//     }
//     dsu[x] = find(dsu[x]);
//     return dsu[x];
// }

// void merge(int x, int y) {
//     x = find(x);
//     y = find(y);
//     if(x == y) {
//         return;
//     }
//     if(sizes[x] == sizes[y]) {
//         dsu[y] = x;
//         sizes[x] += sizes[y];
//     } else {
//         dsu[y] = x;
//         sizes[x] += sizes[y];
//     }
// }

// int comps[200];

// void dfs(int i, int p, int id, vector<vector<array<ll,2>>> &adj) {
//     comps[i] = id;
//     for(auto c : adj[i]) {
//         if(c[0] != p) {
//             dfs(c[0],i,id,adj);
//         }
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m; cin >> n >> m;
//     vector<array<ll,5>> edges;
//     set<ll> gold_amts;
//     ll G, S; cin >> G >> S;

//     for(int i = 0; i < m; i++) {
//         ll x, y, g, s; cin >> x >> y >> g >> s;
//         x--; y--;
//         edges.push_back({x,y,g,s,i});
//         gold_amts.insert(g);
//     }

//     for(int i = 0; i < n; i++) {
//         dsu[i] = i;
//         sizes[i] = 1;
//     }

//     vector<int> ingraph(m);
//     int merges = 0;

//     //first create minimum spanning tree only considering the amounts of silver. Then, we try to slowly decrease the amounts of gold. 
//     priority_queue<array<ll,2>> maxg; //
//     priority_queue<array<ll,2>> maxs;
    
//     //sort in order of increasing silver
//     sort(edges.begin(), edges.end(), [] (const auto &lhs, const auto &rhs) -> bool {
//         return lhs[3] < rhs[3];
//     });

//     vector<vector<array<ll,2>>> adj(n);

//     for(int i = 0; i < m; i++) {
//         array<ll,5> edge = edges[i];
//         if(find(edge[0]) != find(edge[1])) {
//             merges++;
//             merge(edge[0],edge[1]);
//             maxg.push({edge[2], edge[4]});
//             maxs.push({edge[3],edge[4]});
//             ingraph[edge[4]] = 1;
//             adj[edge[0]].push_back({edge[1],edge[4]});
//             adj[edge[1]].push_back({edge[0],edge[4]});
//         }
//         if(merges == n - 1) break;
//     }

//     ll res = LLONG_MAX;

//     vector<ll> golds(gold_amts.begin(), gold_amts.end());
//     reverse(golds.begin(), golds.end());
//     int sidx = 0;
//     bool poss = merges == n - 1;

//     for(int i = 0; i < golds.size() && poss; i++) {
//         ll gold = golds[i];
//         while(maxg.size() && maxg.top()[0] > gold) {
//             ll id = maxg.top()[1];
//             maxg.pop();
//             ingraph[id] = 0;
//             for(int j = 0; j < n; j++) {
//                 for(int k = 0; k < adj[j].size(); k++) {
//                     if(adj[j][k][1] == id) {
//                         adj[j].erase(adj[j].begin() + k);
//                         break;
//                     }
//                 }
//             }

//             memset(comps, 0, sizeof(comps));
//             int comp_id = 1;
//             for(int j = 0; j < n; j++) {
//                 if(comps[j] == 0) {
//                     dfs(j,-1,comp_id++, adj);
//                 }
//             }

//             bool found = 0;
//             while(sidx != m && !found) {
//                 array<ll,5> edge = edges[sidx++];
//                 if(comps[edge[0]] != comps[edge[1]]) {
//                     found = 1;
//                     adj[edge[0]].push_back({edge[1],edge[4]});
//                     adj[edge[1]].push_back({edge[0],edge[4]});
//                     maxg.push({edge[2],edge[4]});
//                     maxs.push({edge[3],edge[4]});
//                     ingraph[edge[4]] = 1;
//                 }
//             }
//             if(!found) poss = 0;
//         }
//         if(poss == 0) break;

//         while(maxs.size() && ingraph[maxs.top()[1]] == 0) {
//             maxs.pop();
//         }

//         res = min(res, maxg.top()[0] * G + maxs.top()[0] * S);

//     }

//     cout << (res == LLONG_MAX ? -1 : res) << '\n';

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

pair<int, array<ll,3>> dfs(int i, int p, int target, vector<vector<array<ll,2>>> &adj) {
    if(i == target) {
        return {1,{}};
    }

    for(auto c : adj[i]) {
        if(c[0] != p) {
            auto p = dfs(c[0],i,target,adj);
            if(p.first) {
                if(c[1] >= p.second[0]) {
                    return {1,{c[1],c[0],i}};
                } else {
                    return p;
                }
            }
        }
    }

    return {0,{}};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    ll G, S; cin >> G >> S;
    vector<array<ll,4>> edges(m);

    for(int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2] >> edges[i][3];
        edges[i][0]--;
        edges[i][1]--;
    }

    //sort by silver
    sort(edges.begin(), edges.end(), [](const auto &lhs, const auto &rhs) -> bool {
        return lhs[3] < rhs[3];
    });

    int cnt = 0;
    vector<vector<array<ll,2>>> adj(n); //destination, gold. 
    multiset<ll> ms;
    ll res = LLONG_MAX;
    for(int i = 0; i < m; i++) {
        array<ll,4> edge = edges[i];
        pair<int,array<ll,3>> p = dfs(edge[0],-1,edge[1],adj);
        ll a = p.second[1];
        ll b = p.second[2];
        if(p.second[0] > edge[2] && p.first) {
            cnt--;
            // cout << "removing edge : " << a << " " << b << " " << p.second[0] << '\n';
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < adj[j].size(); k++) {
                    if(j == a && adj[j][k][0] == b || j == b && adj[j][k][0] == a) {
                        ms.erase(ms.find(adj[j][k][1]));
                        // cout << "erase val : " << adj[j][k][1] << '\n';
                        adj[j].erase(adj[j].begin() + k);
                        break;
                    }
                }
            }
        }

        if(p.first == 0 || edge[2] < p.second[0]) {
            cnt++;
            adj[edge[0]].push_back({edge[1],edge[2]});
            adj[edge[1]].push_back({edge[0],edge[2]});
            ms.insert(edge[2]);
            ms.insert(edge[2]);
        }

        if(cnt == n - 1) {
            // cout << "i : " << i << " p1 : " << (*--ms.end()) << " p2 : " << edge[3] << '\n';
            res = min(res,(*--ms.end()) * G +  edge[3] * S);
        }
    }
    cout << (res == LLONG_MAX ? -1 : res) << '\n';
    return 0;
}