#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 2e5;
int dsu[N];

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
    dsu[x] = y;
}

// const int N = 2e5;
// int dsu[N];
// int depths[N];
// int sizes[N];

// int find(int x) {
//     if(dsu[x] == x) {
//         return x;
//     }
//     dsu[x] = find(dsu[x]);
//     return dsu[x];
// }

// void merge(int x, int y) {
//     x = find(x);
//     y = find(y);
//     if(x == y) {
//         return;
//     }

//     if(sizes[x] == sizes[y]) {
//         dsu[y] = x;
//         depths[x]++;
//         sizes[x] += sizes[y];
//     } else if(sizes[x] < sizes[y]) {
//         dsu[y] = x;
//         sizes[x] += sizes[y];
//     } else {
//         dsu[x] = y;
//         sizes[y] += sizes[x];
//     }
// }

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //read in input
    int n, m; cin >> n >> m;
    //initialize dsu datastructure
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
    }
    //add edges to list
    vector<vector<ll>> v;
    for(int i = 0; i < m; i++) {
        //read in input - first node, second node, edge weight
        int a, b, c; cin >> a >> b >> c;
        a--; b--; //0-index the nodes (currently 1-indexed)
        //add to vector (array) of edges {weight, first node, second node}
        v.push_back({c,a,b});
    }

    //sort the edges by weight of edge
    sort(v.begin(), v.end());

    ll cost = 0;
    int mergecnt = 0;
    //for each loop over sorted edges 
    for(vector<ll> edge : v) {
        int a = edge[1]; //first node
        int b = edge[2]; //second node
        //check if they are in the same dsu group
        if(find(a) != find(b)) {
            //if not, merge and add cost
            mergecnt++;
            merge(a,b);
            cost += edge[0];
        }
    }
    cout << (mergecnt == n - 1 ? to_string(cost) : "IMPOSSIBLE") << '\n';
    return 0;
}