ll flow(vector<unordered_map<int,ll>> &adj, int s, int t) {

    ll res = 0;
    int n = adj.size();
    vector<int> p;

    while(1) {
        p.assign(n,-1);
        queue<int> q;
        q.push(s);
        while(q.size()) {
            int i = q.front();
            q.pop();
            for(auto [c, fl] : adj[i]) {
                if(p[c] == -1) {
                    p[c] = i;
                    q.push(c);
                }
            }
        }

        if(p[t] == -1) {
            break;
        }

        ll bn = LLONG_MAX;
        int cur = t;
        while(cur != s) {
            int par = p[cur];
            bn = min(bn, adj[par][cur]);
            cur = par;
        }
        res += bn;
        cur = t;
        while(cur != s) {
            int par = p[cur];
            adj[par][cur] -= bn;
            if(adj[par][cur] == 0) adj[par].erase(cur);
            adj[cur][par] += bn;
            cur = par;
        }
    }

    return res;

}