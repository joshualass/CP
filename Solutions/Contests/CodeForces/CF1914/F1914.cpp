#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs(int i, vector<vector<int>> &adj, vector<int> &subtree_sizes) {
    for(auto n : adj[i]) {
        dfs(n,adj,subtree_sizes);
        subtree_sizes[i] += subtree_sizes[n];
    }
    subtree_sizes[i]++;
}

void dfs2(int i, int use, vector<vector<int>> &adj, vector<int> &subtree_sizes, int &ans) {
    if(use) { //use on current node
        use--;
    }

    int under = subtree_sizes[i] - 1;
    int most_sub = 0;
    int most_idx = -1;
    
    for(auto child : adj[i]) {
        if(subtree_sizes[child] > most_sub) {
            most_sub = subtree_sizes[child];
            most_idx = child;
        }
    }
    // cout << "i : " << i << " use : " << use << " most sub : " << most_sub << '\n';

    //see if we can use all
    if(most_sub <= use + under - most_sub) {
        under -= use;
        ans += under / 2;
    } else {
        use += under - most_sub;
        ans += under - most_sub;
        dfs2(most_idx,use,adj,subtree_sizes,ans);
    }

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int parent; cin >> parent;
        parent--;
        adj[parent].push_back(i);
    }

    vector<int> subtree_sizes(n);

    dfs(0,adj,subtree_sizes);
    int ans = 0;
    // cout << "ss : " << subtree_sizes << '\n';
    dfs2(0,0,adj,subtree_sizes,ans);
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}