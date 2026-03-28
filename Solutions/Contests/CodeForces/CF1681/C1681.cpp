#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<int> c(n);
    iota(c.begin(), c.end(), 0);

    sort(c.begin(), c.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return a[lhs] + b[lhs] < a[rhs] + b[rhs];
    });

    vector<array<int,2>> ops;

    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);
    for(int i = 0; i < n; i++) {
        if(c[i] != cur[i]) {
            int to = -1;
            for(int j = 0; j < n; j++) {
                if(cur[j] == c[i]) {
                    to = j;
                }
            }
            swap(a[i], a[to]);
            swap(b[i], b[to]);
            swap(cur[i], cur[to]);
            ops.push_back({i, to});
        }
    }

    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;
    // cout << "c : " << c << endl;

    if(is_sorted(a.begin(), a.end()) && is_sorted(b.begin(), b.end())) {
        cout << sz(ops) << '\n';
        for(auto op : ops) cout << op[0] + 1 << " " << op[1] + 1 << '\n';
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}