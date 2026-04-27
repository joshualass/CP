#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void kdfs(int i, vector<vector<int>> &adj, vector<int> &order, vector<int> &vis) {
    vis[i] = 1;
    for(int x : adj[i]) {
        if(vis[x] == 0) {
            kdfs(x,adj,order,vis);
        }
    }
    order.push_back(i);
}

void sdfs(int i, vector<vector<int>> &adj, vector<int> &vis, vector<vector<int>> &sccs) {
    vis[i] = 2;
    sccs.back().push_back(i);
    for(int x : adj[i]) {
        if(vis[x] == 1) {
            sdfs(x,adj,vis,sccs);
        }
    }
}

vector<vector<int>> kosarajus(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> tp(n);
    for(int i = 0; i < n; i++) {
        for(int x : adj[i]) {
            tp[x].push_back(i);
        }
    }
    vector<int> order(n);
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            kdfs(i,adj,order,vis);
        }
    }
    reverse(order.begin(), order.end());
    vector<vector<int>> sccs;
    for(int i = 0; i < n; i++) {
        if(vis[order[i]] == 1) {
            sccs.push_back({});
            sdfs(order[i],tp,vis,sccs);
        }
    }
    return sccs;
}

pair<vector<vector<int>>, vector<int>> compress_SCC(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> a(n);

    vector<vector<int>> sccs = kosarajus(adj);

    vector<int> scc_id(n);
    for(int i = 0; i < sccs.size(); i++) {
        for(int x : sccs[i]) {
            scc_id[x] = i;
        }
    }

    vector<vector<int>> upd_adj(sccs.size());
    set<array<int,2>> edges;
    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) {
            int i_id = scc_id[i], to_id = scc_id[to];
            if(i_id != to_id && edges.count({i_id,to_id}) == 0) {
                upd_adj[i_id].push_back(to_id);
                edges.insert({i_id,to_id});
            }
        }
    }
    return {upd_adj, scc_id};
}

/*
4 3
###
..#
#.#
..#


*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> b(n);
    vector<int> a(m);

    for(auto &x : b) cin >> x;  
    for(auto &x : a) cin >> x;

    vector<vector<int>> marker(n, vector<int>(m));

    for(int i = 0; i < m; i++) {
        for(int j = n - 1; j >= 0; j--) {
            if(a[i] && b[j][i] == '#') {
                marker[j][i] = 1;
                a[i]--;
            }
        }
    }

    vector<vector<int>> vis(n, vector<int>(m, -1));
    vector<vector<array<int,2>>> atcomp;
    vector<int> mark;
    vector<map<int,int>> sands(m);
    int id = 0;

    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            if(vis[i][j] == -1 && b[i][j] == '#') {
                atcomp.push_back({});
                queue<array<int,2>> q;

                int marked = 0;

                auto pushq = [&](int x, int y) -> void {
                    assert(b[x][y] == '#');
                    if(vis[x][y] == -1) {
                        vis[x][y] = id;
                        q.push({x, y});
                    }
                };

                pushq(i, j);

                while(sz(q)) {
                    auto [x, y] = q.front();
                    q.pop();
                    atcomp.back().push_back({x, y});
                    sands[y][x] = id;
                    if(marker[x][y]) marked = 1;
                    for(int dir = 0; dir < 4; dir++) {
                        int nx = x + dx[dir], ny = y + dy[dir];
                        if(nx >= 0 && nx < n && ny >= 0 && ny < m && b[nx][ny] == '#') {
                            pushq(nx, ny);
                        }
                    }
                }

                id++;
                mark.push_back(marked);
            }
        }
    }

    vector<vector<int>> adj(id);

    for(int i = 0; i < id; i++) {
        for(auto [x, y_] : atcomp[i]) {
            for(int d = -1; d <= 1; d++) {
                int y = y_ + d;
                if(y >= 0 && y < m) {
                    auto it = sands[y].upper_bound(x);
                    if(it != sands[y].end()) {
                        adj[i].push_back(it->second);
                    }
                }
            }
        }
    }

    // cout << "vis" << endl;
    // for(auto x : vis) cout << x << endl;

    // cout << "adj" << endl;
    // for(int i = 0; i < id; i++) cout << "i : " << i << " adj[i] : " << adj[i] << endl;

    auto [nx_adj, scc_id] = compress_SCC(adj);

    int s = sz(nx_adj);
    vector<int> ind(s), nx_marked(s);

    for(int i = 0; i < s; i++) {
        for(int to : nx_adj[i]) {
            ind[to]++;
        }
    }

    vector<int> vis2(s, -1), odor(s, -1);
    int zz = 0;

    for(int i = 0; i < id; i++) {
        int leader = scc_id[i];
        if(ind[leader] == 0) {
            queue<int> q;
            q.push(leader);
            while(sz(q)) {
                int x = q.front();
                q.pop();
                if(vis2[x] != -1) continue;
                vis2[x] = leader;
                odor[x] = zz;
                for(int to : nx_adj[x]) q.push(to);
            }
            zz++;
        }
    }

    // cout << "v2 : " << vis2 << endl;

    // cout << "ok0" << endl;

    for(int i = 0; i < id; i++) {
        if(mark[i]) nx_marked[scc_id[i]] = 1;   
    }

    // cout << "ok1" << endl;
    
    vector<int> z;

    for(int i = 0; i < s; i++) {
        if(nx_marked[i]) z.push_back(i);
    }

    // cout << "ok2" << endl;

    sort(z.begin(), z.end(), [&](const int &lhs, const int &rhs) -> bool {
        return odor[lhs] > odor[rhs];
    });

    vector<int> vis3(s);

    // cout << "s : " << s << endl;

    // cout << "ok3" << endl;
    
    int res = 0;
    for(int x : z) {
        // cout << "x : " << x << endl;
        if(vis3[x] == 0) {
            // cout << "mih 0 : " << endl;
            res++;
            queue<int> q;
            q.push(vis2[x]);
            while(sz(q)) {
                int y = q.front();
                q.pop();
                // cout << "y : " << y << endl;
                if(vis3[y]) continue;
                vis3[y] = 1;
                for(int to : nx_adj[y]) q.push(to);
            }
        }
    }

    // cout << "ok4" << endl;
    
    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

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
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m; cin >> n >> m;
//     vector<string> b(n);
//     vector<int> a(n);

//     for(auto &x : b) cin >> x;  
//     for(auto &x : a) cin >> x;

//     vector<vector<int>> vis(n, vector<int>(m));
//     int res = 0;

//     auto disturb = [&](int i, int j) -> void {

//         queue<array<int,2>> q;
//         res++;

//         auto pushq = [&](int x, int y) -> void {
//             assert(b[x][y] == '#');
//             if(vis[x][y] == 0) {
//                 vis[x][y] = 1;
//                 q.push({x, y});
//             }
//         };

//         pushq(i, j);

//         while(sz(q)) {
//             auto [x, y] = q.front();
//             q.pop();
//             if(x + 1 < n) {
//                 b[x+1][y] = '#';
//                 pushq(x + 1, y);
//             }
//             if(y && b[x][y-1] == '#') {
//                 pushq(x, y - 1);
//             }
//             if(y + 1 < m && b[x][y+1] == '#') {
//                 pushq(x, y + 1);
//             }
//         }
//     };

//     vector<array<int,2>> leaders;



//     {
//         vector<vector<int>> vis(n, vector<int>(m));
//         for(int i = 0; i < n; i++) {
//             for(int j = 0; j < m; j++) {
//                 if(vis[i][j] == 0 && b[i][j] == '#') {
//                     array<int,2> lo = {i, j};
//                     queue<array<int,2>> q;

//                     auto pushq = [&](int x, int y) -> void {
//                         assert(b[x][y] == '#');
//                         if(vis[x][y] == 0) {
//                             vis[x][y] = 1;
//                             q.push({x, y});
//                         }
//                     };

//                     pushq(i, j);

//                     while(sz(q)) {
//                         auto [x, y] = q.front();
//                         q.pop();
//                         lo = max(lo, {x, y});
//                         for(int dir = 0; dir < 4; dir++) {
//                             int nx = x + dx[dir], ny = y + dy[dir];
//                             if(nx >= 0 && nx < n && ny >= 0 && ny < m && b[nx][ny] == '#') {
//                                 pushq(nx, ny);
//                             }
//                         }
//                     }
//                     leaders.push_back(lo);
//                 }
//             }
//         }
//     }

//     sort(leaders.begin(), leaders.end());

//     // cout << "leaders : " << leaders << endl;

//     for(auto [i, j] : leaders) {
//         if(b[i][j] == '#' && vis[i][j] == 0) {
//             disturb(i, j);
//         }
//     }

//     cout << res << '\n';

//     return 0;
// }
