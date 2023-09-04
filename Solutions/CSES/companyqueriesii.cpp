#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//LCA in log(n) time
const int N = 2e5;
const int P = 20;
int edges[N][P];
vector<vector<int>> revs;
int depths[N];

void dfs(int n, int d) {
    depths[n] = d;
    for(auto x : revs[n]) {
        dfs(x, d + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    revs.assign(n, {});
    edges[0][0] = 0;
    for(int i = 1; i < n; i++) {
        int num; cin >> num;
        num--;
        edges[i][0] = num;;
        revs[num].push_back(i);
    }
    for(int p = 1; p < P; p++) {
        for(int i = 0; i < n; i++) {
            edges[i][p] = edges[edges[i][p-1]][p-1];
        }
    }

    dfs(0, 0);

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(depths[a] > depths[b]) {
            swap(a,b);
        }
        int move = depths[b] - depths[a];
        int p = 0;
        while(move != 0) {
            if(move & 1) {
                b = edges[b][p];
            }
            move >>= 1;
            p++;
        }
        if(a == b) {
            cout << ++a << "\n";
        } else {
            int p = P - 1;
            while(p >= 0) {
                if(edges[a][p] != edges[b][p]) {
                    a = edges[a][p];
                    b = edges[b][p];
                }
                p--;
            }
            if(a == b) {
                cout << ++a << "\n";
            } else {
                cout << edges[a][0] + 1 << "\n";
            }
        }
    }

    return 0;
}