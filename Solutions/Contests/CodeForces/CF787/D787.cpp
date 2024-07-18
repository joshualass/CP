#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
nice problem! 
observe - once we visit an element that fits into a range of type 3, we can just add it to our dijkstra's we won't get anything better because there are no negative edges!

how to add ranges and find and remove ranges that contain an element now? 
we use segtree ofc
*/

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

struct InvertedTree {
    vector<vector<int>> s; int n;
    InvertedTree(int n = 0) : s(n*2), n(n) {}
    void update(int l, int r, int u) { //increases values in [l,r) by u. Just add to each vector
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                s[l].push_back(u);
                l++;
            }
            if(r & 1) {
                r--;
                s[r].push_back(u);
            }
        }
    }
    vector<int> query(int pos, vector<int> &vis3) { //queries the value of element at pos
        pos += n;
        vector<int> res;
        pos *= 2;
        while(pos /= 2) {
            // cout << "pos : " << pos << " starting size : " << s[pos].size() << '\n';
            while(s[pos].size()) {
                if(vis3[s[pos].back()] == 0) {
                    res.push_back(s[pos].back());
                    vis3[s[pos].back()] = 1;
                }
                s[pos].pop_back();
            }
        }
        return res;
    }
};

void visit(int i, vector<vector<array<ll,3>>> &type2, vector<array<ll,4>> &type3, InvertedTree &tree, ll dist, vector<int> &vis3, set<int> &unvis, vector<ll> &res, priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> &pq) {
    res[i] = dist;
    unvis.erase(i);
    
    // cout << "me visto s : " << i << endl;
    for(int j = 0; j < type2[i].size(); j++) {
        // cout << "push2 ? " << type2[i][j] << endl;
        pq.push({dist + type2[i][j][2], 2, i, j});
    }

    vector<int> type3s = tree.query(i, vis3);
    for(int x : type3s) {
        // cout << "push3 ? " << type3[x] << endl;
        pq.push({dist + type3[x][0], 3, x, -1});
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q, s; cin >> n >> q >> s;
    vector<vector<array<ll,3>>> type2(n); // {from, {l, r, w}}
    vector<array<ll,4>> type3; //{w, l, r, dest}
    InvertedTree tree(n);
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int v, u, w; cin >> v >> u >> w;
            v--; u--;
            type2[v].push_back({u,u,w});
            // cout << "init t1 from v : " << v << " data : " << type2[v].back() << endl;
        } else if(type == 2) {
            int v, l, r, w; cin >> v >> l >> r >> w;
            v--; l--; r--;
            type2[v].push_back({l,r,w});
            // cout << "init t2 from v : " << v << " data : " << type2[v].back() << endl;
        } else {
            int v, l, r, w; cin >> v >> l >> r >> w;
            v--; l--; r--;
            tree.update(l, r + 1, type3.size());
            type3.push_back({w,l,r,v});
            // cout << "init t3 from v : " << type3.back() << endl;
        }
    }

    vector<int> vis3(type3.size());
    set<int> unvis;
    vector<ll> res(n,-1);
    for(int i = 0; i < n; i++) {
        unvis.insert(i);
    }

    priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> pq; // {distance, type, i, j for type 2}
    visit(s - 1, type2, type3, tree, 0, vis3, unvis, res, pq);

    while(pq.size()) {
        array<ll,4> a = pq.top();
        pq.pop();
        // cout << "a : " << a << endl;
        if(a[1] == 2) {
            auto [l, r, w] = type2[a[2]][a[3]];
            // cout << "l : " << l << " r : " << r << " w : " << w << endl;
            set<int>::iterator it = unvis.lower_bound(l);
            while(it != unvis.end() && *it <= r) {
                visit(*it, type2, type3, tree, a[0], vis3, unvis, res, pq);
                it = unvis.lower_bound(l);
            }
        } else {
            auto [w, l, r, dest] = type3[a[2]];
            // cout << "w : " << w << " l : " << l << " r : " << r << " Dest : " << dest << endl;
            if(res[dest] == -1) {
                visit(dest, type2, type3, tree, a[0], vis3, unvis, res, pq);
            }
        }
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }

    return 0;
}

//I don't think this works
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// struct InvertedTree {
//     vector<deque<int>> s; int n;
//     InvertedTree(int n = 0) : s(n*2), n(n) {}
//     void update(int l, int r, int u) { //increases values in [l,r) by u
//         for(l += n, r += n; l < r; l /= 2, r /= 2) {
//             if(l & 1) {
//                 s[l].push_back(u);
//                 l++;
//             }
//             if(r & 1) {
//                 r--;
//                 s[r].push_back(u);
//             }
//         }
//     }
//     int query(int pos, vector<array<ll,4>> &type3, vector<ll> &vis, int maxweight) { //queries the value of element at pos
//         int ans = -1;
//         while(pos /= 2) {
//             while(s[pos].size() && vis[type3[s[pos].front()][3]] != -1) {
//                 s[pos].pop_front();
//             }
//             if(s[pos].size() && type3[s[pos].front()][0] <= maxweight) {
//                 if(ans == -1 || ans != -1 && type3[s[pos].front()][0] < type3[ans][0]) {
//                     ans = s[pos].front();
//                 }
//             }
//         }
//         return ans;
//     }
// };

// void visit(vector<ll> &vis, priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> &pq, int i, ll dist, vector<vector<array<ll,3>>> &type2) {
//     vis[i] = dist;
//     for(int j = 0; j < type2[i].size(); j++) {
//         pq.push({dist + type2[i][j][2], i, j});
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q, s; cin >> n >> q >> s;
//     //use [] inclusive ranges
//     vector<vector<array<ll,3>>> type2(n); //idx is v, {l, r, w}
//     vector<array<ll,4>> type3; // w, l, r, v  
//     InvertedTree tree(n);

//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int v, u, w; cin >> v >> u >> w;
//             u--; v--;
//             type3.push_back({w, v, v, u});
//         } else if(type == 2) {
//             int v, l, r, w; cin >> v >> l >> r >> w;
//             v--; l--; r--;
//             type2[v].push_back({l,r,w});
//         } else {
//             int v, l, r, w; cin >> v >> l >> r >> w;
//             v--; l--; r--;
//             type3.push_back({w, l, r, v});
//         }
//     }

//     sort(type3.begin(), type3.end());

//     for(int i = 0; i < type3.size(); i++) {
//         tree.update(type3[i][1], type3[i][2] + 1, i);
//     }

//     int type3p = 0;
//     set<int> unvis;
//     for(int i = 0; i < n; i++) unvis.insert(i);
//     vector<ll> vis(n,-1);
//     priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq; //{d, i, j}

//     visit(vis,pq,s-1,0,type2);

//     while(1) {
//         //first try an edge from dijkstra from type 2
//         if(pq.size()) {
//             array<ll,3> a = pq.top();
//             array<ll,3> edge = type2[a[1]][a[2]];
//             set<int>::iterator it = unvis.lower_bound(edge[0]);
//             if(it != unvis.end() && *it <= edge[1]) {
//                 int tryv = *it;

//             } else {
//                 pq.pop();
//             }
//         } else {

//         }


//     }


//     return 0;
// }