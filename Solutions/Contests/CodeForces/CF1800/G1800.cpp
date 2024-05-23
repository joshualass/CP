#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;
mt19937 rng;
ll ihash[200000];
int depths[200000];

/*
how to do polynomial hash on rooted tree
We define the polynomial P(G) for a rooted tree G as follows. If G is a single leaf, P(G) = 1. Otherwise, let d be the depth of the tree, k be the number of children of the root of G, and G_1, G_2, ..., G_d be the subtrees corresponding to those children. Define P(G) = (x_d + P(G_1))(x_d + P(G_2))...(x_d + P(G_k)).
*/

bool isPrime(int n);

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_hash(ll l, ll r) {
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

void depthdfs(int i, int p, int d, vector<vector<int>> &adj) {
    depths[i] = d;
    for(int c : adj[i]) {
        if(c != p) {
            depthdfs(c,i,d+1,adj);
        }
    }
}

void dfs(int i, int p, vector<vector<int>> &adj, vector<ll> &hashes, vector<bool> &issym) {
    vector<int> h;
    map<ll,int> m;
    for(int c : adj[i]) {
        if(c != p) {
            dfs(c,i,adj,hashes,issym);
            ll hash = hashes[c];
            h.push_back(c);
            if(m.count(hash)) {
                m.erase(hash);
            } else {
                m[hash] = c;
            }
        }
    }
    if(m.empty() || m.size() == 1 && issym[(*m.begin()).second]) {
        issym[i] = 1;
    }
    ll currhash = 1;
    for(int i = 0; i < h.size(); i++) {
        currhash = currhash * (ihash[depths[h[i]]] + hashes[h[i]]) % MOD;
    }
    hashes[i] = currhash;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> hashes(n);
    vector<bool> issym(n);
    depthdfs(0,-1,0,adj);
    dfs(0,-1,adj,hashes,issym);
    cout << (issym[0] ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    MOD = gen_hash(900000000,1000000000);

    for(int i = 0; i < 200000; i++) {
        ihash[i] = rng() % 69696969 + 1;
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}