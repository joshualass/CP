#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 200000;
int dsu[N*2];
int lifts[N*2][20];
int depths[N*2];
int n;

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

int LCA(int a, int b) {
    if(a == b) return 0;
    if(find(a) != find(b)) return -1; //never in same group
    if(depths[b] > depths[a]) {
        swap(a,b);
    }
    int movea = depths[a] - depths[b];
    int p = 19;
    while(p >= 0) {
        if(movea & (1 << p)) {
            a = lifts[a][p];
        }
        p--;
    }
    p = 19;
    while(p >= 0) {
        if(lifts[a][p] != lifts[b][p]) {
            a = lifts[a][p];
            b = lifts[b][p];
        }
        p--;
    }
    if(a != b) {
        a = lifts[a][0];
    }
    return a - n + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, q; cin >> n >> m >> q;
    
    for(int i = 0; i < N * 2; i++) {
        dsu[i] = i;
        lifts[i][0] = i;
    }
    vector<vector<int>> adj(N * 2);
    vector<bool> heads(N*2,true);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a = find(--a);
        b = find(--b);
        if(a != b) {
            dsu[a] = i + n;
            dsu[b] = i + n;
            lifts[a][0] = i + n;
            lifts[b][0] = i + n;
            adj[i+n].push_back(a);
            adj[i+n].push_back(b);
            heads[a] = false;
            heads[b] = false;
            heads[i+n] = true;
        } else {
            heads[i+n] = false;
        }

    }
    for(int i = 0; i < N*2; i++) {
        if(heads[i]) {
            queue<pair<int,int>> q;
            q.push({i,0});
            while(q.size()) {
                pair<int,int> p = q.front();
                q.pop();
                depths[p.first] = p.second;
                for(auto x : adj[p.first]) {
                    q.push({x,p.second+1});
                }
            }
        }
    }

    for(int p = 1; p < 20; p++) {
        for(int i = 0; i < N * 2; i++) {
            lifts[i][p] = lifts[lifts[i][p-1]][p-1];
            if(p == 1) {
                // cerr << lifts[i][0] << " ";
            }
        }
    }
    // cerr << "\n";

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << LCA(--a,--b) << "\n";
    }


    return 0;
}