#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    swap(n,m);
    priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq;
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        pq.push({r - 1, l - 1});
    }

    ll res = 0;
    for(int i = 0; i < n; i++) {
        while(pq.size() && pq.top()[1] < i) {
            pq.pop();
        }
        res += (pq.size() ? pq.top()[0] - 1 : n - 1) - i + 1;
    }

    cout << res << '\n';

    return 0;
}