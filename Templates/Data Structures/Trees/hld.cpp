//very general HLD template that you can do a lot of fun things with :)
struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> tin, tout, depths, par, heads, starts;
    //heads[i] => for node i, the node with least depth that contains node i in its heavy path
    //starts[i] => where in contiguous memory this point is. 

    HLD(vector<vector<int>> adj) {
        this->adj = adj;
        build();
    }

    void build() {
        this->n = adj.size();
        tin.assign(n, -1);
        tout.assign(n, -1);
        depths.assign(n, -1);
        par.assign(n, -1);

        int time = 0;

        auto euler = [&](auto self, int i, int p, int d) -> void {
            tin[i] = time++;
            depths[i] = d;
            par[i] = p;
            for(int c : adj[i]) {
                if(c != p) {
                    self(self, c, i, d + 1);
                }
            }
            tout[i] = time;
        };

        euler(euler, 0, -1, 0);

        heads.assign(n, -1);
        starts.assign(n, -1);

        time = 0;
        auto hld = [&](auto self, int i, int p, int head) -> void {
            if(head == -1) {
                head = i;
            }

            heads[i] = head;
            starts[i] = time++;

            int hc = -1;
            for(int c : adj[i]) {
                if(c != p) {
                    if(hc == -1 || tout[c] - tin[c] > tout[hc] - tin[hc]) {
                        hc = c;
                    }
                }
            }

            if(hc == -1) return;

            self(self, hc, i, head);
            for(int c : adj[i]) {
                if(c != p && c != hc) {
                    self(self, c, i, -1);
                }
            }
        };

        hld(hld, 0, -1, -1);

        // cout << "tin : " << tin << '\n';
        // cout << "tout : " << tout << '\n';
        // cout << "depths : " << depths << '\n';
        // cout << "par : " << par << '\n';
        // cout << "heads : " << heads << '\n';
        // cout << "starts : " << starts << '\n';

    }

    int lca(int a, int b) {
        while(heads[a] != heads[b]) {
            if(depths[heads[a]] > depths[heads[b]]) {
                a = par[heads[a]];
            } else {
                b = par[heads[b]];
            }
        }
        if(depths[a] < depths[b]) {
            return a;
        } else {
            return b;
        }
    }

    //lca + dist work, see https://cses.fi/problemset/result/15390705/
    int dist(int a, int b) {
        int unc = lca(a, b);
        return depths[b] + depths[a] - depths[unc] * 2;
    }

    vector<array<int,2>> path(int a, int b) {
        vector<array<int,2>> res;

        auto append_path = [&](int cur, int depth) -> void {
            if(depths[cur] < depth) return;
            while(1) {
                if(depths[heads[cur]] <= depth) {
                    int l = starts[heads[cur]] + (depth - depths[heads[cur]]), r = starts[cur] + 1;
                    res.push_back({l, r});
                    break;
                }
                int l = starts[heads[cur]], r = starts[cur] + 1;
                res.push_back({l, r});
                cur = par[heads[cur]];
            }
        };

        int unc = lca(a, b);
        int unc_depth = depths[unc];

        append_path(a, unc_depth);
        int sz = res.size();
        append_path(b, unc_depth + 1);
        reverse(res.begin() + sz, res.end());
        return res;
    }

    // int query(int a, int b, Tree &tree) {
    //     int res = 0;

    //     auto append_path = [&](int cur, int depth) -> void {
    //         if(depths[cur] < depth) return;
    //         while(1) {
    //             if(depths[heads[cur]] <= depth) {
    //                 res = tree.f(res, tree.query(starts[heads[cur]] + (depth - depths[heads[cur]]), starts[cur] + 1));
    //                 break;
    //             }
    //             res = tree.f(res, tree.query(starts[heads[cur]], starts[cur] + 1));
    //             cur = par[heads[cur]];
    //         }
    //     };

    //     int unc = lca(a, b);
    //     int unc_depth = depths[unc];

    //     append_path(a, unc_depth);
    //     append_path(b, unc_depth + 1);
    //     return res;
    // }
};