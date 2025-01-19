#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
Tried some silly strategies before
On day of solve, first tried solving for each subpermutation and adding appending a row/col each time to see if possible. but approach is no good.
Second approach was to iterate over the rows and place a 1 for any position that was less than or equal to, but this did the opposite of what we wanted.
Third approach, do the reverse behavior. Essentially, for both rows and columns, they form subsets of each other, differing by a single 0/1 at the same time.
 */

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> p(n), q(n);
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        p[--x] = i;
    }

    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        q[--x] = i;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << (q[j] >= n - p[i] + 1);
        }
        cout << '\n';
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> a;
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= n; j++) {
//             a.push_back(i*j);
//         }
//     }
//     sort(a.begin(),a.end());
//     int magic = a[n*n/2];

//     vector<int> p(n), q(n);
//     for(int &x : p) cin >> x;
//     for(int &x : q) cin >> x;

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             cout << (p[i] + q[j] > n) << " \n"[j == n - 1];
//         }
//     }

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<class T>
// pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;
//     vector<unordered_map<int,T>> trace(graph.size());

//     for(;;) {
//         fill(par.begin(), par.end(), -1);
//         par[source] = 0;
//         int ptr = 1;
//         q[0] = source;

//         for(int i = 0; i < ptr; i++) {
//             int x = q[i];
//             for(auto e : graph[x]) {
//                 if(par[e.first] == -1 && e.second > 0) {
//                     par[e.first] = x;
//                     q[ptr++] = e.first;
//                     if(e.first == sink) goto out;
//                 }
//             }
//         }
//     return {flow,trace};
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         trace[p][y] += inc;
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         trace[y][p] -= inc;
//         }
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<unordered_map<int,int>> adj(n * 2 + 2);
//     int sc = n * 2, sk = n * 2 + 1;

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             adj[i][j+n] = 1;
//         }
//     }

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         adj[sc][i] = x;
//     }

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         adj[n+i][sk] = x;
//     }

//     for(int i = )

//     // auto [flow, trace] = edmondsKarp(adj, sc, sk);

//     // for(int i = 0; i < n; i++) {
//     //     for(int j = 0; j < n; j++) {
//     //         cout << trace[i][j+n] << " \n"[j == n - 1];
//     //     }
//     // }

//     return 0;
// }