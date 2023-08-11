//works for connected graph without cycles (tree)
void dfs(int v, int par, int h, vector<int> &d, vector<vector<int>> &adj) {
    d[v] = h;
    for (int i : adj[v]) {
        if (i != par) {
            dfs(i, v, h + 1, d, adj);
        }
    }
}
