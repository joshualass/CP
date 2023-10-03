//fills vector<vector<T>> jumps with the binary jumps. 
template<typename T>
void buildJumps(vector<T> &edges, vector<vector<T>> &jumps, int depth = 64) {
    jumps.assign(edges.size(), vector<T>(depth));
    for(int i = 0; i < depth; i++) {
        for(int j = 0; j < edges.size(); j++) {
            if(i == 0) jumps[j][i] = (edges[j] == -1 ? j : edges[j]);
            else jumps[j][i] = jumps[jumps[j][i-1]][i-1];
        }
    }
}