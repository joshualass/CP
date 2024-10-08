#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 2e5;
int dsu[N];
int sizes[N];

void dsubuild(int n) {
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }
}

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

void solve() {
    
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        sizes[i] = 1;
    }

    vector<vector<int>> stops(n, vector<int>(10));
    vector<vector<int>> starts(n, vector<int>(10));

    for(int i = 0; i < m; i++) {
        int a, d, k; cin >> a >> d >> k;
        a--;
        starts[a][d - 1]++;
        if(a + d * (k + 1) < n) {
            stops[a + d * (k + 1)][d-1]++;
        }
    }

    int merges = 0;
    for(int d = 1; d <= 10; d++) {
        for(int start = 0; start < min(d,n); start++) {

            int c = starts[start][d-1];
            for(int i = start + d; i < n; i += d) {
                c -= stops[i][d-1];
                if(c) {
                    if(find(i-d) != find(i)) {
                        merges++;
                    }
                    // cout << "attempt merge d : " << d << " start : " << start << " i : " << i << " merging : " << i - d << " to " << i << '\n';
                    merge(i-d,i);
                }
                c += starts[i][d-1];
            }

        }
    }

    cout << n - merges << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}