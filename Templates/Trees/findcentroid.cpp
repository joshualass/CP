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