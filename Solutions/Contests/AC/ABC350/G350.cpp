#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const int MAXN = 100000;
const int SQN = 316;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll xl = 0;
    int n, q; cin >> n >> q;

    vector<pb_set<int>> adj(n);//the neighbors of each node
    vector<pb_set<int>> large_nei(n);//the neighbors of each node that have degree > SQN
    vector<pb_map<int,int>> large_connection(n); //all pairs of large connections

    for(int i = 0; i < q; i++) {
        ll A, B, C; cin >> A >> B >> C;
        ll a = ((A * (1 + xl)) % MOD) % 2;
        ll b = ((B * (1 + xl)) % MOD) % n;
        ll c = ((C * (1 + xl)) % MOD) % n;
        if(a == 0) {
            adj[b].insert(c);
            adj[c].insert(b);

            if(adj[b].size() == SQN + 1) {
                for(int nei : adj[b]) {
                    for(int p : large_nei[nei]) {
                        large_connection[p][b] = nei;
                        large_connection[b][p] = nei;
                    }
                    large_nei[nei].insert(b);
                }
            } else if(adj[b].size() > SQN) {
                int nei = c;
                for(int p : large_nei[nei]) {
                    large_connection[p][b] = nei;
                    large_connection[b][p] = nei;
                }
                large_nei[nei].insert(b);
            }
            swap(b,c);
            if(adj[b].size() == SQN + 1) {
                for(int nei : adj[b]) {
                    for(int p : large_nei[nei]) {
                        large_connection[p][b] = nei;
                        large_connection[b][p] = nei;
                    }
                    large_nei[nei].insert(b);
                }
            } else if(adj[b].size() > SQN) {
                int nei = c;
                for(int p : large_nei[nei]) {
                    large_connection[p][b] = nei;
                    large_connection[b][p] = nei;
                }
                large_nei[nei].insert(b);
            }
        } else {
            if(adj[b].size() > adj[c].size()) swap(b,c);
            int found = -1;
            if(adj[b].size() <= SQN) {
                for(int nei : adj[b]) {
                    if(adj[c].find(nei) != adj[c].end()) {
                        found = nei;
                    }
                }
            } else {
                if(large_connection[b].find(c) != large_connection[b].end()) {
                    found = large_connection[b][c];
                }
            }
            found++;
            cout << found << '\n';
            xl = found;
        }
    }

    return 0;
}