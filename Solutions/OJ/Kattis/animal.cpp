#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    auto parse = [](string s) -> pair<vector<vector<int>>, vector<int>> {
        vector<vector<int>> adj;
        vector<int> leafs;
        stack<int> st;
        int cur_num = 0;
        for(char c : s) {
            if(c == '(') {
                int nx = sz(adj);
                if(st.size()) {
                    adj[st.top()].push_back(nx);
                }
                adj.push_back({});
                leafs.push_back(0);
                st.push(nx);
            } else if(c == ')') {
                if(cur_num) {
                    int nx = sz(adj);
                    adj[st.top()].push_back(nx);
                    adj.push_back({});
                    leafs.push_back(cur_num);
                    cur_num = 0;
                }
                st.pop();
            } else if(c == ',') {
                if(cur_num) {
                    int nx = sz(adj);
                    adj[st.top()].push_back(nx);
                    adj.push_back({});
                    leafs.push_back(cur_num);
                    cur_num = 0;
                }
            } else {
                cur_num = cur_num * 10 + (c - '0');
            }
        }
        if(cur_num) {
            adj.push_back({});
            leafs.push_back(cur_num);
        }
        return {adj, leafs};
    };

    string s1, s2; cin >> s1 >> s2;
    auto [a1, l1] = parse(s1);
    auto [a2, l2] = parse(s2);

    vector<array<ll,5>> h(n);
    for(auto &x : h) for(auto &y : x) y = rng() % 6767676767LL;
    set<array<ll,5>> set1, set2;
    
    auto dfs = [](auto self, int i, vector<vector<int>> &adj, vector<int> &l, vector<array<ll,5>> &h, set<array<ll,5>> &s) -> array<ll,5> {
        array<ll,5> cur = {};
        for(int c : adj[i]) {
            auto ch = self(self, c, adj, l, h, s);
            for(int j = 0; j < 5; j++) cur[j] += ch[j];
        }
        if(l[i]) {
            for(int j = 0; j < 5; j++) cur[j] += h[l[i]-1][j];
        }
        s.insert(cur);
        return cur;
    };

    dfs(dfs, 0, a1, l1, h, set1);
    dfs(dfs, 0, a2, l2, h, set2);

    int res = 0;
    for(auto x : set1) {
        if(set2.count(x)) res++;
    }

    cout << res << '\n';

    return 0;
}
