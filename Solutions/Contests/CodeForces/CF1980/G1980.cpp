#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// const int depth = 31;

// struct Trie {
//     int cnt;
//     Trie* arr[2];
//     Trie() {
//         cnt = 0;
//         arr[0] = nullptr;
//         arr[1] = nullptr;
//     }
// };

// void insert(int num, Trie* root) {
//     Trie* curr = root;
//     for(int d = depth - 1; d >= 0; d--) {
//         int bit = (num >> d) & 1;
//         if(curr->arr[bit] == nullptr) {
//             curr->arr[bit] = new Trie();
//         }
//         curr = curr->arr[bit];
//         curr->cnt++;
//     }
// }

// int query(int num, Trie* root) { //queries the maximum xor value 
//     Trie* curr = root;
//     int ans = 0;
//     for(int d = depth - 1; d >= 0; d--) {
//         int bit = (num >> d) & 1;
//         if(curr->arr[bit ^ 1] && curr->arr[bit ^ 1]->cnt) {
//             curr = curr->arr[bit^1];
//             ans += 1 << d;
//         } else if(curr->arr[bit] && curr->arr[bit]->cnt)  {
//             curr = curr->arr[bit];
//         }
//     }
//     return ans;
// }

// bool find(int num, Trie* root) {
//     Trie* curr = root;
//     for(int d = depth - 1; d >= 0; d--) {
//         if(curr->arr[(num >> d) & 1] == nullptr) return 0;
//         curr = curr->arr[(num >> d) & 1];       
//     }
//     return 1;
// }

// bool erase(int num, Trie* root) { //return 1 if element was removed, 0 if element DNE
//     bool contains = find(num,root);
//     if(contains) {
//         Trie* curr = root;
//         for(int d = depth - 1; d >= 0; d--) {
//             curr = curr->arr[(num >> d) & 1];
//             curr->cnt--;
//         }
//     }
//     return contains;
// }

// void printHelper(Trie* root, int currdepth, int value) { 
//     Trie* curr = root;
//     if(currdepth == -1) {
//         cout << "value : " << value << " cnt : " << curr->cnt << '\n';
//     } else {
//         if(curr->arr[0] && curr->arr[0]->cnt) printHelper(curr->arr[0],currdepth-1, value);
//         if(curr->arr[1] && curr->arr[1]->cnt) printHelper(curr->arr[1],currdepth-1, value + (1 << currdepth));
//     }
// }

// void print(Trie* root) { //prints all values and cnts in Trie
//     printHelper(root, depth - 1, 0);
// }

struct Trie {
    const int depth = 31;
    struct Node {
        array<int,2> a;
        int cnt;
        Node() {
            a = {-1,-1};
            cnt = 0;
        }
    };
    vector<Node> nodes;

    Trie () {
        nodes.push_back(Node());
    }

    void insert(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] == -1) {
                nodes[curr].a[bit] = nodes.size();
                nodes.push_back(Node());
            }
            curr = nodes[curr].a[bit];
            nodes[curr].cnt++;
        }
    }

    int query(int num) {
        int res = 0;
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = (((num >> i) & 1) ^ 1);
            if(nodes[curr].a[bit] != -1 && nodes[nodes[curr].a[bit]].cnt > 0) {
                res += (1 << i);
                curr = nodes[curr].a[bit];
            } else if(nodes[curr].a[bit ^ 1] != -1 && nodes[nodes[curr].a[bit ^ 1]].cnt > 0) {
                curr = nodes[curr].a[bit ^ 1];
            } else {
                return -1;
            }
        }
        return res;
    }

    bool find(int num) {
        int curr = 0;
        for(int i = depth - 1; i >= 0; i--) {
            int bit = ((num >> i) & 1);
            if(nodes[curr].a[bit] != -1) {
                curr = nodes[curr].a[bit];
            } else {
                return 0;
            }
        }
        return 1;
    }

    bool erase(int num) {
        if(find(num)) {
            int curr = 0;
            for(int i = depth - 1; i >= 0; i--) {
                curr = nodes[curr].a[((num >> i) & 1)];
                nodes[curr].cnt--;
            }
            return 1;
        } else {
            return 0;
        }
    }
};

void dfs(int i, int p, int depth, int curr, vector<Trie> &roots, vector<int> &depths, vector<int> &paths, vector<vector<pair<int,int>>> &adj) {

    paths[i] = curr;
    depths[i] = depth&1;
    roots[depths[i]].insert(paths[i]);

    for(pair<int,int> nei : adj[i]) {
        if(nei.first != p) {
            dfs(nei.first,i,depth+1,curr ^ nei.second,roots,depths,paths,adj);
        }
    }

}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<Trie> roots(2);
    vector<int> depths(n);
    vector<int> paths(n);
    dfs(0,-1,0,0,roots,depths,paths,adj);

    int globalxor = 0;

    for(int i = 0; i < m; i++) {
        char type; cin >> type;
        if(type == '^') {
            int y; cin >> y;
            globalxor ^= y;
        } else {
            int v, x; cin >> v >> x;
            v--;
            // erase(paths[v],roots[depths[v]&1]);
            roots[depths[v]&1].erase(paths[v]);
            //currxor is xor from root node to node v
            int currxor = paths[v] ^ x;
            if(depths[v] & 1) {
                currxor ^= globalxor;
            }
            // int evendepth = query(currxor, roots[0]);
            int evendepth = roots[0].query(currxor);
            // int odddepth = query(currxor ^ globalxor, roots[1]);
            int odddepth = roots[1].query(currxor ^ globalxor);
            cout << max(evendepth, odddepth) << ' ';
            // insert(paths[v],roots[depths[v]&1]);
            roots[depths[v]&1].insert(paths[v]);
        }
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}