#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5;
const int P = 20;

int edges[N][P];
int depths[N];
vector<vector<int>> adj;

void dfs(int n, int p, int d) {
    depths[n] = d;
    for(int x : adj[n]) {
        if(x != p) {
            edges[x][0] = n;
            dfs(x, n, d + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    adj.assign(n,{});
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    edges[0][0] = 0;
    dfs(0,-1,0);
    for(int p = 1; p < P; p++) {
        for(int i = 0; i < n; i++) {
            edges[i][p] = edges[edges[i][p-1]][p-1];
        }
    }
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        --a;
        --b;
        if(depths[a] > depths[b]) {
            swap(a,b);
        }
        int moves = depths[b] - depths[a];
        int k = moves;
        int p = 0;
        while(k != 0) {
            if(k & 1) {
                b = edges[b][p];
            }
            k >>= 1;
            p++;
        }
        p = P - 1;
        while(p != -1) {
            if(edges[a][p] != edges[b][p]) {
                moves += (1 << p) * 2;
                a = edges[a][p];
                b = edges[b][p];
            }
            p--;
        }
        if(a != b) {
            moves += 2;
        }
        cout << moves << "\n";
    }


    return 0;
}