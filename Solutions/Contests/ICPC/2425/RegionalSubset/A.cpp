#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int paths, probes; cin >> paths >> probes;
    vector<pair<pi, pi>> adj(11234, {{0, 0}, {0, 0}});
    for (int i = 0; i < paths; ++i) {
        int len_path; cin >> len_path;
        int curr_node = 1;
        for (int j = 0; j < len_path; ++j) {
            char dir; cin >> dir;
            int est_len; cin >> est_len;
            int num_ants; cin >> num_ants;
            char neic; cin >> neic;

            if (dir == 'L') {
                adj[curr_node].first = {neic - 'a' + 1, num_ants};
            } else
                adj[curr_node].second = {neic - 'a' + 1, num_ants};
            curr_node = neic - 'a' + 1;
        }
    }

    vector<vector<int>> dp(1123, vector<int>(1123, -1e9));

    auto f = [&](auto f, int v, int avail) -> int {

        if (dp[v][avail] >= 0) {
            return dp[v][avail];
        }
        
        if ((adj[v].first.first == 0) && (adj[v].second.first == 0)) {
            return 0;
        }
        
        if (adj[v].first.first == 0) {
            // no left 
            return f(f, adj[v].second.first, avail) + adj[v].second.second;
        } else if (adj[v].second.first == 0) {
            return f(f, adj[v].first.first, avail) + adj[v].first.second;
        }
        
        // convolution
        int mx = 0;
        int le_nei = adj[v].first.first, ri_nei = adj[v].second.first;
        int le_wei = adj[v].first.second, ri_wei = adj[v].second.second;
        for (int i = 1; i < avail; ++i) {
            mx = max(mx, f(f, le_nei, i) + le_wei + f(f, ri_nei, avail - i) + ri_wei);
        }


        mx = max(mx, f(f, le_nei, avail) + le_wei);
        mx = max(mx, f(f, ri_nei, avail) + ri_wei);

        return dp[v][avail] = mx;
        
    };

    cout << f(f, 1, probes) << endl;

    return 0;
}