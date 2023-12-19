#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<int,ll>>> adj(n); //{index, label}
    vector<vector<pair<int,ll>>> trans(n);
    for(int i = 0; i < m; i++) {
        int a, b, l; cin >> a >> b >> l;
        a--; b--;
        adj[a].push_back({b,l});
        trans[b].push_back({a,l});
    }

    vector<int> indegrees(n);
    for(auto x : adj) {
        for(auto y : x) {
            indegrees[y.first]++;
        }
    }
    queue<pair<int,int>> q;
    vector<vector<vector<pair<int,ll>>>> groups(n,vector<vector<pair<int,ll>>>(1)); //{index, score}
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push({i,0});
        }
    }

    vector<int> top;
    vector<int> depths(n);
    while(q.size()) {
        pair<int,int> p = q.front();
        int i = p.first;
        top.push_back(i);
        q.pop();
        if(adj[i].size() == 0) {
            groups[0][0].push_back({i, 0});
        }
        for(auto x : adj[i]) {
            indegrees[x.first]--;
            depths[x.first] = max(depths[x.first], p.second + 1);
            if(indegrees[x.first] == 0) {
                q.push({x.first, p.second + 1});
            }
        }
    }

    vector<array<ll,3>> dp(n);

    //fails sample case 3
    for(int i = n - 1; i >= 0; i--) {
        int idx = top[i];
        array<ll,3> curr = dp[idx];
        for(auto road : trans[idx]) {
            int next_idx = road.first;
            ll upd_length = curr[0] + 1;
            ll upd_label = road.second;
            ll upd_score = curr[2] + road.second;
            if(upd_length > dp[next_idx][0] || upd_length == dp[next_idx][0] && upd_label < dp[next_idx][1]) {
                dp[next_idx] = {upd_length, upd_label, upd_score};
            }

        }

    }
    
    vector<bool> visited(n);

    //wrong direction
    
    vector<ll> ans(n);
    for(int depth = 0; depth < n; depth++) {
        // cout << "depth : " << depth << '\n';
        vector<array<ll,5>> helpme;
        for(auto group : groups[depth]) {
            // cout << group << '\n';
            for(auto node : group) {
                for(auto rev_edge : trans[node.first]) {
                    helpme.push_back({rev_edge.second, rev_edge.first, node.first, depth + 1, node.second + rev_edge.second});
                }
            }
        }
        stable_sort(helpme.begin(), helpme.end(), [](const array<ll,5> &lhs, const array<ll,5> &rhs) {
            return lhs[0] < rhs[0];
        });
        int prev_label = -1;
        for(auto arr : helpme) {
            if(visited[arr[1]] || dp[arr[1]][0] != arr[3]) continue;
            visited[arr[1]] = 1;
            ans[arr[1]] = arr[4];
            if(arr[0] != prev_label) {
                groups[arr[3]].push_back({});
                prev_label = arr[0];
            }
            groups[arr[3]].back().push_back({arr[1], arr[4]});
        }
    }

    for(int i = 0; i < n; i++) {
        cout << dp[i][0] << " " << ans[i] << '\n';
    }


    return 0;
}