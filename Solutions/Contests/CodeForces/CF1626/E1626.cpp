#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
I solved with quite a bit of casework
Editorial uses the idea to look at each individual directed edge and see if it's possible to always be able to move in that direction.
It is always possible if when removing edge, the component of the destination is >= 2. 

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
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
    
    int n; cin >> n;
    int root = -1;
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        if(b[i]) root = i;
    }

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> cnts(n);

    auto calcSS = [&](auto self, int i, int p) -> void {
        int cnt = b[i];
        for(int c : adj[i]) {
            if(c != p) {
                self(self,c,i);
                cnt += cnts[c];
            }
        }
        cnts[i] = cnt;
    };
    
    calcSS(calcSS, root, -1);

    cerr << "root : " << root << '\n';

    int all = 0;
    vector<int> res(n);

    auto markposs = [&](auto self, int i, int p) -> void {
        if(res[i]) return;;
        res[i] = 1;
        for(int c : adj[i]) {
            if(c != p) {
                self(self,c,i);
            }
        }
    };

    auto dfs = [&](auto self, int i, int p) -> array<int,2> {
        int closest = MOD;
        if(b[i]) {
            closest = 0;
            for(int c : adj[i]) {
                if(c != p) {
                    if(cnts[c]) {
                        all = 1;
                    }
                }
            }
            markposs(markposs, i, p);
        } else {
            vector<array<int,2>> closests;
            for(int c : adj[i]) {
                if(c != p) {
                    closests.push_back(self(self,c,i));
                    closest = min(closest, closests.back()[0]);
                }
            }
            sort(closests.begin(), closests.end());
            // cout << "i : " << i << " closests : " << closests << '\n';
            if(closests.size() >= 2 && closests[0][0] == 1 && closests[1][0] < MOD) {
                all = 1;
            }
            if(closests.size() && closests[0][0] == 1) {
                res[i] = 1;
                for(int j = 1; j < closests.size(); j++) {
                    markposs(markposs, closests[j][1], i);
                }
            }
        }
        return {closest + 1, i};
    };

    int subcnt = 0;

    for(int c : adj[root]) {
        if(cnts[c] == 0) {
            markposs(markposs, c, root);
        } else {
            dfs(dfs,c,root);
            vector<int> hasblack;
            vector<int> noblack;
            for(int cc : adj[c]) {
                if(cc != root) {
                    if(cnts[cc]) {
                        hasblack.push_back(cc);
                    } else {
                        noblack.push_back(cc);
                    }
                }
            }
            if(hasblack.size() >= 2) {
                all = 1;
            }
            res[c] = 1;
            for(int cc : noblack) {
                markposs(markposs, cc, c);
            }
            subcnt++;
        }
    }

    if(subcnt >= 2) {
        all = 1;
    }

    res[root] = 1;

    cerr << "all : " << all << '\n';
    for(int i = 0; i < n; i++) {
        cout << (res[i] | all) << " \n"[i == n - 1];
    }

    return 0;
}