//Discussed with Andrew and he gave me solution. Implementation feels like a chore now. 
//greedy approach doesn't really work

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

void solve() {
    
    int n, m; cin >> n >> m;

    vector<pb_map<int,int>> sadj(n);
    vector<pb_map<int,int>> fadj(n);
    vector<int> selfs(n);

    int globalid = 0;

    for(int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        if(c) {
            if(u == v) {
                selfs[u]++;
            } else {
                fadj[u][globalid] = v;
                fadj[v][globalid++] = u;
            }
        } else {
            if(u != v) {
                sadj[u][globalid] = v;
                sadj[v][globalid++] = u;
            }
        }
    }

    stack<int> unsat;
    stack<int> toprune;

    for(int i = 0; i < n; i++) {
        if(fadj[i].size() & 1) {
            unsat.push(i);
        }
        if(sadj[i].size() == 1) {
            toprune.push(i);
        }
    }

    int ok = 1;

    while(unsat.size()) {
        if(toprune.size()) {
            int i = toprune.top();
            toprune.pop();

            if(sadj[i].empty()) {
                continue;
            }

            auto [id, v] = (*sadj[i].begin());

            if(fadj[i].size() & 1) {
                fadj[i][globalid] = v;
                fadj[v][globalid++] = i;
            }

            sadj[i].erase(id);
            sadj[v].erase(id);

            if(sadj[v].size() == 1) {
                toprune.push(v);
            }

            if(fadj[v].size() & 1) {
                unsat.push(v);
            }

        } else {

            int i = unsat.top();
            unsat.pop();

            if(fadj[i].size() & 1) {
                if(sadj[i].empty()) {
                    ok = 0;
                    break;
                }
                auto [id, v] = (*sadj[i].begin());

                sadj[i].erase(id);
                sadj[v].erase(id);

                fadj[i][globalid] = v;
                fadj[v][globalid++] = i;

                if(sadj[i].size() == 1) {
                    toprune.push(i);
                }

                if(sadj[v].size() == 1) {
                    toprune.push(v);
                }

                if(fadj[v].size() & 1) {
                    unsat.push(v);
                }

            }

        }
    }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " to :";
    //     for(auto [id, dest] : fadj[i]) {
    //         cout << " " << dest;
    //     }
    //     cout << '\n';
    // }

    if(ok) {
        cout << "Yes\n";

        vector<int> res;

        auto dfs = [&](auto self, int i) -> void {
            while(fadj[i].size()) {
                auto [id, v] = (*fadj[i].begin());
                fadj[i].erase(id);
                fadj[v].erase(id);
                self(self, v);
            }
            res.push_back(i);
            while(selfs[i]) {
                res.push_back(i);
                selfs[i]--;
            }
        };

        dfs(dfs, 0);

        cout << res.size() - 1 << '\n';
        for(int i = 0; i < res.size(); i++) {
            cout << res[i] + 1 << " \n"[i == res.size() - 1];
        }

    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}