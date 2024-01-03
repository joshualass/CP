vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) { //for trees
    for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }