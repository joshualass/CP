#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
To kind of solve this problem, for each node, we need to figure out how many nodes are at a distance from 0 to n - 1 away from it.
This is difficult to do efficiently, so we use the help of hashing and rerooting the tree. 

Transitions aren't tricky from node to node when rerooting; we just multiply by our multiplier.

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

vector<int> solve(vector<vector<int>> &adj, vector<ll> &a, ll MOD, ll mult) {

    vector<ll> mults(adj.size());
    mults[0] = 1;
    for(int i = 1; i < adj.size(); i++) {
        mults[i] = mults[i-1] * mult % MOD;
    }

    ll ihash = 0;
    for(ll x : a) {
        ihash += mults[x];
    }

    set<ll> posshash;
    for(int i = 0; i < adj.size(); i++) {
        posshash.insert((ihash + mults[i]) % MOD);
    }

    vector<ll> hashessubt(adj.size());
    
    auto dfs1 = [&](auto self, int i, int p) -> void {

        ll cnt = 0;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                cnt += hashessubt[c];
            }
        }

        hashessubt[i] = (cnt % MOD * mult + 1) % MOD;

    };

    dfs1(dfs1, 0, -1);

    vector<int> res(adj.size());
    vector<ll> truehashes(adj.size());

    auto dfs2 = [&](auto self, int i, int p) -> void {

        if(p == -1) {
            truehashes[i] = hashessubt[i];
        } else {
            
            ll ph = truehashes[p];
            ll contribtoph = hashessubt[i] * mult % MOD;

            ll undocontrib = (ph - contribtoph + MOD) % MOD;

            truehashes[i] = (undocontrib * mult + hashessubt[i]) % MOD;

        }

        if(posshash.count(truehashes[i])) {
            res[i] = 1;
        }

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }

    };

    dfs2(dfs2, 0, -1);

    // cout << "res : " << res << '\n';
    // cout << "posshash : " << posshash << '\n';
    // cout << "truehashes : " << truehashes << '\n';

    return res;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> a(n - 1);
    for(ll &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> res(n);

    for(int t = 0; t < 2; t++) {
        ll mod = gen_prime(9e8, 1e9);
        ll mult = rng() % mod;
        vector<int> rest = solve(adj,a,mod,mult);
        for(int i = 0; i < n; i++) {
            res[i] += rest[i];
        }
    }

    cout << count(res.begin(), res.end(),2) << '\n';

    for(int i = 0; i < n; i++) {
        if(res[i] == 2) {
            cout << i + 1 << " ";
        }
    }

    cout << '\n';

    return 0;
}