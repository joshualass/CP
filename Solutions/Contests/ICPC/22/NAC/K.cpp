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
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p, m; cin >> n >> p >> m;
    vector<int> b(n);
    for(int i = 0; i < p; i++) {
        int x; cin >> x;
        b[x-1] = 1;
    }

    vector<vector<pair<int,char>>> adj(n), radj(n);
    for(int i = 0; i < m; i++) {
        int s1, s2;
        char c;
        cin >> s1 >> c >> s2;
        s1--; s2--;
        adj[s1].push_back({s2,c});
        radj[s2].push_back({s1,c});
    }

    vector<pair<int,string>> vis(n);
    queue<pair<int,string>> q;
    q.push({0,""});

    while(q.size()) {
        queue<pair<int,string>> q0;
        q0.push(q.front());
        q.pop();
        vector<pair<int,string>> ve;
        while(q0.size()) {
            auto [i, s] = q0.front();
            q0.pop();
            if(vis[i].first) continue;
            vis[i] = {1,s};
            for(auto [nei, c] : adj[i]) {
                if(c >= 'a') {
                    q0.push({nei, s});
                } else {
                    q.push({nei, s + string(1,c)});
                }
            }
        }
    }


    string res = string(1000,'z');
    for(int i = 0; i < n; i++) {
        if(b[i] && vis[i].first && vis[i].second.size() < res.size()) res = vis[i].second;
    }
    
    cout << "vis : " << vis << '\n';
    cout << "res : " << res << '\n';

    if(res == string(1000, 'z')) {
        cout << "-1\n";
        return 0;
    }

    vector<int> a(n, 1e9);
    vector<vector<int>> visd(n,vector<int>(res.size()));

    queue<array<int,2>> qd;
    qd.push({0,0});
    while(qd.size()) {
        queue<array<int,2>> q0;
        q0.push(qd.front());
        qd.pop();
        while(q0.size()) {
            auto [i, j] = q0.front();
            q0.pop();
            if(visd[i][j]) continue;
            visd[i][j] = 1;
            for(auto [nei, c] : adj[i]) {
                if(c >= 'a') {
                    q0.push({nei, j});
                } else {
                    if(j == res.size() || res[j] != c) {
                        a[nei] = min(a[nei], j + 1);
                    } else if(res[j] == c) {
                        qd.push({nei, j + 1});
                    }
                }
            }
        }
    }

    vector<int> visr(n,-1);
    queue<array<int,2>> qr;
    for(int i = 0; i < n; i++) {
        if(b[i]) qr.push({i,0});
    }

    while(qr.size()) {
        queue<array<int,2>> q0;
        q0.push(qr.back());
        qr.pop();
        while(q0.size()) {
            auto [i, j] = q0.front();
            q0.pop();
            if(visr[i] != -1) continue;
            visr[i] = j;
            for(auto [nei, c] : radj[i]) {
                if(c >= 'a') {
                    q0.push({nei,j});
                } else {
                    qr.push({nei, j + 1});
                }
            }
        }
    }

    int bl = 1e9;
    for(int i = 0; i < n; i++) {
        if(a[i] != 1e9 && visr[i] != -1) bl = min(bl, a[i] + visr[i]);
    }

    cout << res.size() + bl << '\n';

    return 0;
}