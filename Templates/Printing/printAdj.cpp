void printAdj(const vector<vector<int>> &adj) {
    cout << "adj:\n";
    for(int i = 0; i < adj.size(); i++) {
        cout << "i: " << i << " -";
        for(int x : adj[i]) {
            cout << " " << x;
        }
        cout << "\n";
    }
}