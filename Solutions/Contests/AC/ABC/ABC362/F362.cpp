#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int MAXN = 2e5;
int subtree_sizes[MAXN];
 
void calc_subtree_size(int i, int p, vector<vector<int>> &adj) {
    int sz = 1;
    for(int c : adj[i]) {
        if(c != p) {
            calc_subtree_size(c,i,adj);
            sz += subtree_sizes[c];
        }
    }
    subtree_sizes[i] = sz;
}
 
vector<int> find_centroids(int i, int p, vector<vector<int>> &adj, int n) {
    for(int c : adj[i]) {
        if(c != p) {
            if(subtree_sizes[c] > n / 2) {
                return find_centroids(c,i,adj,n);
            } else if(n % 2 == 0 && subtree_sizes[c] == n / 2) {
                return {i,c};
            }
        }
    }
    return {i};
}

void dfs(int i, int p, vector<vector<int>> &adj, vector<int> &tree, int avoid) {

    tree.push_back(i);
    for(int c : adj[i]) {
        if(c != p && c != avoid) {
            dfs(c,i,adj,tree,avoid);
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
 
    for(int i = 0; i < n - 1; i++) { //for trees
        int a, b; cin >> a >> b;
        a--; b--; //1 -> 0 indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    calc_subtree_size(0,-1,adj);

    vector<int> centroids = find_centroids(0,-1,adj,n);

    // cout << "make here" << endl;

    // cout << "centroids : " << centroids << endl;

    if(centroids.size() == 2) {
        vector<int> tree1, tree2;
        dfs(centroids[0], -1, adj, tree1, centroids[1]);
        dfs(centroids[1], -1, adj, tree2, centroids[0]);

        assert(tree1.size() == tree2.size());

        for(int i = 0; i < tree1.size(); i++) {
            cout << tree1[i] + 1 << " " << tree2[i] + 1 << "\n";
        }

    } else {
        vector<vector<int>> trees;
        priority_queue<array<int,2>> pq;
        for(int c : adj[centroids[0]]) {
            trees.push_back({});
            dfs(c,centroids[0], adj, trees.back(), centroids[0]);
            pq.push({(int) trees.back().size(), (int) trees.size() - 1});
        }
        if(n % 2 == 0) {
            trees.push_back({centroids[0]});
            pq.push({(int) trees.back().size(), (int) trees.size() - 1});
        }

        while(pq.size() >= 2) {
            array<int,2> first = pq.top();
            pq.pop();
            array<int,2> second = pq.top();
            pq.pop();
            cout << trees[first[1]].back() + 1 << " " << trees[second[1]].back() + 1 << '\n';
            trees[first[1]].pop_back();
            trees[second[1]].pop_back();
            if(trees[first[1]].size()) {
                pq.push({(int) trees[first[1]].size(), first[1]});
            }
            if(trees[second[1]].size()) {
                pq.push({(int) trees[second[1]].size(), second[1]});
            }
        }

    }
    
    return 0;
}