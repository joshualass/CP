// http://www.usaco.org/index.php?page=viewproblem2&cpid=789

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void printV(const vector<int> &x) {
    // cout << " --- vector --- ";
    for(int y : x) {
        cout << y << "\n";
    }
    // cout << "\n";
}

const int N = 1e5;
int dsu[N];
int depths[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("mootube.in","r",stdin);
    freopen("mootube.out","w",stdout);
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }
    vector<vector<int>> adj(0);
    for(int i = 0; i < n - 1; i++) {
        int p, q, r; cin >> p >> q >> r;
        p--; q--;
        adj.push_back({r,p,q});
    }    
    sort(adj.begin(), adj.end());
    vector<vector<int>> queries(0);
    for(int i = 0; i < q; i++) {
        int k, v; cin >> k >> v;
        v--;
        queries.push_back({k,v,i});
    }

    sort(queries.begin(),queries.end());
    vector<int> ans(q);
    while(queries.size()) {
        vector<int> query = *--queries.end(); //k, v, i
        queries.pop_back();
        while(adj.size() && query[0] <= (*--adj.end())[0]) {
            vector<int> last = (*--adj.end());
            adj.pop_back();
            merge(last[1],last[2]);
        }
        ans[query[2]] = sizes[find(query[1])] - 1;
    }
    printV(ans);

    return 0;
}