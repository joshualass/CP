#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        merge(a,b);
    }
    vector<pair<int,int>> roads(0);
    for(int i = 1; i < n; i++) {
        if(find(0) != find(i)) {
            roads.push_back({1,i+1});
            merge(0,i);
        }
    }
    cout << roads.size() << "\n";
    for(auto &x: roads) cout << x.first << " " << x.second << "\n";
    return 0;
}