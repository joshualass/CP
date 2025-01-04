#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ttfang

/*
observe that for each color the graph for of only that color looks like a tree when we use as many edges as possible. 
Therefore, can use at mos 2 * n + m - 2 edges / color
To construct the graph, it's easiest to construct when we first fix 

*/

void solve() {
    int n, m; cin >> n >> m;
    if(m > n * 2 - 1) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    vector adj(n * 2, vector<int>(n * 2 - 1, -1));
    for(int i = 0; i < n * 2; i++) {
        for(int j = 0; j < n * 2 - 1; j++) {
            adj[(i + j) % (n * 2)][j] = i / 2;
        }
    }
    for(int i = 0; i < n * 2; i++) {
        for(int j = 0; j < m; j++) {
            cout << adj[i][j] + 1 << " \n"[j == m - 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}