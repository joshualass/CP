#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void dfs(int i, int p, vector<vector<int>> &adj, vector<int> &parents) {
    parents[i] = p;
    for(int c : adj[i]) {
        if(c != p) dfs(c,i,adj,parents);
    }
}

void dfs2(int i, int p, int depth, vector<vector<int>> &adj, vector<int> &depths) {
    depths[i] = depth;
    for(int c : adj[i]) {
        if(c != p) {
            dfs2(c,i,depth + 1, adj, depths);
        }
    }
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> colors(n);
    for(int &x : colors) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> p(n);
    dfs(0,-1,adj,p);
    vector<int> d(n);
    dfs2(0,-1,0,adj,d);

    int bc = 0;
    vector<bool> black(n);
    vector<int> black_p(n);

    vector<int> zeroes;   //stores all black nodes with 0 childrens that are black
    priority_queue<pair<int,int>> pq;   //stores max heap for number of black children
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> mindepth; //stores lowest depth that is black

    for(int i = 0; i < n; i++) {
        int u = colors[i];
        black[i] = u;
        if(u) {
            mindepth.push({d[i],i});
            bc++;
            if(p[i] != -1) {
                black_p[p[i]]++;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        zeroes.push_back(i);
        if(black_p[i] >= 2) {
            pq.push({black_p[i],i});
        }
    }

    // cout << "starting zeroes : " << zeroes << '\n';
    // cout << "starting black_p : " << black_p << '\n';
    // cout << "startind depths : " << d << '\n';

    for(int i = 0; i < q; i++) {
        int u; cin >> u;
        u--;
        if(black[u] == 0) { // toggling on
            black[u] = 1;
            bc++;
            mindepth.push({d[u],u});
            int pidx = p[u];
            if(pidx != -1) {
                black_p[pidx]++;
                if(black_p[pidx] >= 2) {
                    pq.push({black_p[pidx],pidx});
                }
            }
            if(black_p[u] >= 2) pq.push({black_p[u],u});
            zeroes.push_back(u);
        } else {
            bc--;
            black[u] = 0;
            int pidx = p[u];
            if(pidx != -1) {
                black_p[pidx]--;
                if(black_p[pidx] >= 2) {
                    pq.push({black_p[pidx],pidx});
                }
                zeroes.push_back(pidx);
            }
        }
        // cout << "query # : " << i << '\n';
        // cout << "intermediate zeroes : " << zeroes << '\n';
        // cout << "intermediate black_p : " << black_p << '\n';
        if(bc == 0) {
            cout << "No\n";
            continue;
        }
        
        set<int> zerocnts;
        while(zeroes.size() && zerocnts.size() < 3) {
            int x = zeroes.back();
            zeroes.pop_back();
            if(black[x] && black_p[x] == 0) zerocnts.insert(x);
        }

        vector<pair<int,int>> sigma;
        set<int> sigma_helper;
        while(pq.size() && sigma.size() < 2) {
            pair<int,int> p = pq.top();
            pq.pop();
            int x = p.second;
            int cnt = p.first;
            if(black[x] && black_p[x] == cnt) {
                if(sigma_helper.count(x) == 0) {
                    sigma_helper.insert(x);
                    sigma.push_back({cnt,x});
                }
            }
        }

        int lo = INT_MAX;
        while(1) {
            pair<int,int> p = mindepth.top();
            // cout << "p : " << p.first << " " << p.second << '\n';
            int depth = p.first, x = p.second;
            if(black[x]) {
                lo = x;
                break;
            }
            mindepth.pop();
        }
        // cout << "zero size : " << zerocnts.size() << " sigma size : " << sigma.size() << " lo : " << lo << '\n';
        // if(sigma.size()) {
        //     cout << "sigma : " << sigma[0].first << " " << sigma[0].second << '\n';
        // }
        if(zerocnts.size() == 1 && sigma.size() == 0 || zerocnts.size() == 2 && sigma.size() == 1 && lo == sigma[0].second) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }

        for(int x : zerocnts) zeroes.push_back(x);
        for(auto p : sigma) pq.push(p);

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}