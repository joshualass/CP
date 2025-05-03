#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
    dsu[y] = x;
    sizes[x] += sizes[y];
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        int n; cin >> n;
        if(n == -1) break;
        vector<array<ld,3>> a(n);
        for(auto &x : a) for(auto &y : x) cin >> y;

        dsubuild(n);

        int res = 1;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ld dist = sqrtl((a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1]));
                if(dist <= a[i][2] + a[j][2] && dist >= abs(a[i][2] - a[j][2])) {
                    // cout << "merge i : " << i << " j : " << j << '\n';
                    merge(i, j);
                }
            }
        }

        for(int i = 0; i < n; i++) res = max(res, sizes[find(i)]);
        cout << "The largest component contains " << res << " ring" << (res == 1 ? "" : "s") << ".\n";
    }

    return 0;
}
