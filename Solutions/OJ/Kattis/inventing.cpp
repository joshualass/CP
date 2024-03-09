#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 2e5;
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

void solve() {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }
    vector<vector<int>> v(n - 1,vector<int>(3));
    ll ans = 0;
    for(int i = 0; i < n - 1; i++) {
        cin >> v[i][1] >> v[i][2] >> v[i][0];
        v[i][1]--;
        v[i][2]--;
        ans += v[i][0];
    }
    sort(v.begin(), v.end());

    for(int i = 0; i < n - 1; i++) {
        int a = find(v[i][1]);
        int b = find(v[i][2]);
        ll asize = sizes[a];
        ll bsize = sizes[b];
        ans += (asize * bsize - 1) * (v[i][0] + 1);
        merge(a,b);
    }
    cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}