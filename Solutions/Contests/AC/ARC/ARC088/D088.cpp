#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int odd_cnt = 0;
    int leaf_root = -1;
    for(int i = 0; i < n; i++) {
        odd_cnt += adj[i].size() & 1;
        if(adj[i].size() == 1) leaf_root = i;
    }

    int a = odd_cnt / 2;

    auto poss = [&](int mp) -> bool {
        int ok = 1;

        auto can_self_match = [&](vector<int> &child_paths, int exclude) -> bool {
            for(int i = 0, j = child_paths.size() - 1; i < child_paths.size(); i++, j--) {
                if(i == exclude) i++;
                if(j == exclude) j--;
                if(i < child_paths.size() && j >= 0 && child_paths[i] + child_paths[j] > mp) return 0;
            }
            return 1;
        };

        auto dfs = [&](auto self, int i, int p) -> int {
            vector<int> child_paths;
            for(int c : adj[i]) {
                if(c != p) {
                    child_paths.push_back(self(self, c, i));
                }
            }

            sort(child_paths.begin(), child_paths.end());

            if(child_paths.empty()) return 1;

            if(child_paths.size() % 2 == 0) {
                if(can_self_match(child_paths, -1)) {
                    return 1;
                }
                child_paths.pop_back();
            }

            int l = 0, r = child_paths.size();
            while(l != r) {
                int m = (l + r) / 2;
                if(can_self_match(child_paths, m)) {
                    r = m;
                } else {
                    l = m + 1;
                }
            }
            if(l == child_paths.size() || child_paths[l] == mp && i != leaf_root) {
                ok = 0;
                return 0;
            }
            return child_paths[l] + 1;
        };
        dfs(dfs, leaf_root, -1);
        return ok;
    };
    
    int l = 1, r = n - 1;
    while(l != r) {
        int m = (l + r) / 2;
        if(poss(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << a << " " << l << '\n';

    return 0;
}