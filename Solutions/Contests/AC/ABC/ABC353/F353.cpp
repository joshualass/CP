#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const int MAXN = 16;

int dp[MAXN + 1][1 << MAXN];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b,-c});
        adj[b].push_back({a,c});
    }

    vector<pair<int,vector<pair<int,int>>>> groups; //{bm, list of pair {id, shift}}}
    vector<int> vis(n,-1);

    for(int i = 0; i < n; i++) {
        if(vis[i] == -1) {
            int curr = groups.size();
            vector<pair<int,int>> v;
            queue<pair<int,int>> q;
            q.push({i,0});
            while(q.size()) {
                pair<int,int> p = q.front();
                q.pop();
                if(vis[p.first] == -1) {
                    vis[p.first] = curr;
                    v.push_back({p.first,p.second});
                    for(pair<int,int> to : adj[p.first]) {
                        q.push({to.first,to.second+p.second});
                    }
                }
            }
            sort(v.begin(), v.end(), [] (const auto &lhs, const auto &rhs) -> bool {
                return lhs.second < rhs.second;
            });
            int lo = INT_MAX;
            for(pair<int,int> p : v) {
                lo = min(lo,p.second);
            }
            int bit = 0;
            for(pair<int,int> &p : v) {
                p.second -= lo;
                bit |= 1 << p.second;
            }
            groups.push_back({bit,v});
        }
    }


    vector<set<int>> poss(n);

    int g = groups.size();
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= g; i++) {
        dp[0][0] = i;
        for(int j = 0; j < g; j++) {//n
            for(int bm = (1 << n) - 1; bm >= 0; bm--) {//2^n
                if(dp[j][bm] == i) {
                    for(int shift = 0; shift < n; shift++) {//n
                        int addbm = groups[j].first << shift;
                        if(__builtin_popcount(addbm & ((1 << n) - 1)) == groups[j].second.size() && addbm + bm == (addbm | bm)) {//shift is ok, and not already added
                            dp[j+1][addbm | bm] = i;
                            if(j == g - 1) {
                                for(auto p : groups[j].second) {//n only last time
                                    poss[p.first].insert(shift + p.second);
                                }
                            }
                        }
                    }

                }
            }
        }


        auto m = groups.back();
        groups.pop_back();
        groups.insert(groups.begin(),m);
    }

    for(int i = 0; i < n; i++) {
        if(poss[i].size() == 1) {
            cout << (*poss[i].begin()) + 1;
        } else {
            cout << "-1";
        }
        cout << " \n"[i == n - 1];
    }

    return 0;
}