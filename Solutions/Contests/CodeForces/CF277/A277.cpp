#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 2e5;
int dsu[N];
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
        sizes[x] += sizes[y];
    } else {
        dsu[y] = x;
        sizes[x] += sizes[y];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    for(int i = 0; i < N; i++) {
        dsu[i] = i;
        if(i >= m && i < n + m) {
            sizes[i] = 1;
        } else {
            sizes[i] = 0;
        }
    }
    bool alllost = 1;
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        if(k) alllost = 0;
        int prev = m+i;
        for(int j = 0; j < k; j++) {
            int num; cin >> num;
            num--;
            merge(prev,num);
            prev = num;
        }
    }

    int merges = -1;
    vector<bool> vis(N);

    for(int i = 0; i < N; i++) {
        int x = find(i);
        if(sizes[x] && vis[x] == 0) {
            vis[x] = 1;
            merges++;
        }
    }

    cout << (alllost ? n : merges) << '\n';
    return 0;
}