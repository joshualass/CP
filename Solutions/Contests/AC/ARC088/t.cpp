#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

vector<vector<int>> adj(100000);
vector<int> order, par(100000);
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cin >> n;
    // for(int i = 1; i < n; i++) {
    //     int a, b; cin >> a >> b;
    //     a--; b--;
    //     adj[a].push_back(b);
    //     adj[b].push_back(a);
    // }
    int n = 100000;
    for(int i = 1; i < n; i++) {
        adj[i].push_back(i-1);
        adj[i-1].push_back(i);
    }

    // vector<int> order, par(n);
    auto dfs_2 = [&](auto self, int i, int p) -> void {
        for(int c : adj[i]) if(c != p) self(self,c,i);
        order.push_back(i);
        par[i] = p;
    };
    dfs_2(dfs_2,0,-1);

    int odd_cnt = 0;
    for(int i = 0; i < n; i++) {
        odd_cnt += adj[i].size() & 1;
    }

    int a = odd_cnt / 2;

    auto poss = [&](int mp) -> bool {
        int ok = 1;

        // cout << "mp : " << mp << '\n';

        auto can_self_match = [&](vector<int> &child_paths, int exclude) -> bool {
            for(int i = 0, j = child_paths.size() - 1; i < child_paths.size(); i++, j--) {
                if(i == exclude) i++;
                if(j == exclude) j--;
                if(i < child_paths.size() && j >= 0 && child_paths[i] + child_paths[j] > mp) return 0;
            }
            return 1;
        };

        vector<int> dp(n);
        for(int idx = 0; idx < n; idx++) {
            int i = order[idx];

            vector<int> child_paths;
            for(int c : adj[i]) {
                if(c != par[i]) {
                    // child_paths.push_back(self(self, c, i));
                    child_paths.push_back(dp[c]);
                }
            }

            sort(child_paths.begin(), child_paths.end());

            if(child_paths.empty()) {
                dp[i] = 1;
                continue;
            }

            if(child_paths.size() % 2 == 0) {
                if(can_self_match(child_paths, -1)) {
                    dp[i] = 1;
                    continue;
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
            if(l == child_paths.size() || child_paths[l] == mp && i) {
                ok = 0;
                return 0;
            }
            dp[i] = child_paths[l] + 1;
        }
        return 1;
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