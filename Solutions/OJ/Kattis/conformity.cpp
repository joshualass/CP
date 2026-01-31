#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<set<int>, int> m;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int z = 5;
        set<int> s;
        for(int j = 0; j < 5; j++) {
            int x; cin >> x;
            s.insert(x);
        }
        m[s]++;
    }

    int res = 0, cnt = 0;
    for(auto [k, v] : m) {
        // cout << "v : " << v << endl;
        if(v > res) {
            res = v;
            cnt = v;
        } else if(v == res) cnt += v;
    }

    cout << cnt << '\n';

    return 0;
}
