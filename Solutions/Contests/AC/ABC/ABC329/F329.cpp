#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    vector<set<int>> v(n);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        v[i].insert(num);
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(v[a].size() > v[b].size()) {
            swap(v[a],v[b]);
        }
        for(auto num : v[a]) {
            v[b].insert(num);
        }
        v[a].clear();
        cout << v[b].size() << '\n';
    }

    return 0;
}