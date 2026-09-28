#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
maybe dijkstra doesn't work because there isn't a good way to greedy. 
Instead, just do several monotonic maps. 

Why did dijkstra'ing by delay not work? 
It's possible that we can have a situation where some train is limited by another train, but not by the one with highest delay. It's possible that a train that is delayed less
can delay a certain train more because the train that can delay more even though it has less delay can do so by having a later t. 

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, x; cin >> n >> m >> x;
    vector<array<int,5>> edges(m);
    vector<map<int,int>> delays(n);

    for(int i = 0; i < m; i++) {
        int a, b, s, t; cin >> a >> b >> s >> t;
        a--; b--;
        edges[i] = {a,b,s,t,i};

        if(i == 0) {
            delays[b][t] = x + t;
        }
    }

    sort(edges.begin(), edges.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[2] < rhs[2];
    });
    vector<int> res(m);

    for(auto [a, b, s, t, id] : edges) {

        int delay = 0;
        if(delays[a].upper_bound(s) != delays[a].begin()) {
            int prev = (*--delays[a].upper_bound(s)).second;
            delay = max(0, prev - s);
        }

        res[id] = delay;

        while(1) {
            map<int,int>::iterator it = delays[b].lower_bound(t);
            if(it != delays[b].end() && it->second < t + delay) {
                delays[b].erase(it);
            } else {
                break;
            }
        }

        map<int,int>::iterator lb = delays[b].upper_bound(t);
        if(lb == delays[b].begin() || (--lb)->second < t + delay) {
            delays[b][t] = t + delay;
        }

    }

    for(int i = 1; i < m; i++) {
        cout << res[i] << " \n"[i == m - 1];
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long double ld;
// using namespace std;

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, m, x1; cin >> n >> m >> x1;
//     vector<vector<array<int,4>>> adj(n);

//     int sb, st;

//     for(int i = 0; i < m; i++) {
//         int a, b, s, t; cin >> a >> b >> s >> t;
//         a--; b--;
//         adj[a].push_back({b,s,t,i});
//         if(i == 0) {
//             sb = b;
//             st = t;
//         }
//     }

//     for(int i = 0; i < n; i++) {
//         sort(adj[i].begin(), adj[i].end(), [](const auto &lhs,  const auto &rhs) {
//             return lhs[1] < rhs[1];
//         });

//         // cout << "i : " << i << " edge order : " << adj[i] << '\n';

//     }

//     vector<int> res(m,-1);
//     priority_queue<array<int,4>> pq;
//     pq.push({x1, st, sb, 0});

//     while(pq.size()) {
//         array<int,4> edge = pq.top();
//         auto [xi, ti, i, idi] = edge;
//         pq.pop();

//         // cout << "visit edge : " << edge << '\n';
//         res[idi] = xi;
        
//         while(adj[i].size() && adj[i].back()[1] >= ti) {
//             pq.push({max(0, xi + ti - adj[i].back()[1]), adj[i].back()[2], adj[i].back()[0], adj[i].back()[3]});
//             adj[i].pop_back();
//         }

//         if(adj[i].size()) {
//             // cout << "this edge did not get pushed : " << adj[i].back() << '\n';
//         }

//     }

//     for(int i = 1; i < m; i++) {
//         cout << max(res[i], 0) << " \n"[i == m - 1];
//     }

//     return 0;
// }