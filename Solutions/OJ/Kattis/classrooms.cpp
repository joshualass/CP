#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    multiset<int> s;
    for(int i = 0; i < k; i++) {
        s.insert(0);
    }

    int res = 0;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[1] < rhs[1];
    });

    for(int i = 0; i < n; i++) {
        multiset<int>::iterator it = s.lower_bound(a[i][0]);
        if(it != s.begin()) {
            it--;
            res++;
            s.erase(it);
            s.insert(a[i][1]);
        }
    }

    cout << res << '\n';

    return 0;
}