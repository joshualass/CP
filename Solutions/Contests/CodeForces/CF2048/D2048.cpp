#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, m; cin >> n >> m;
    int kev; cin >> kev;
    vector<int> better, b(m);
    for(int i = 1; i < n; i++) {
        int x; cin >> x;
        if(x > kev) better.push_back(x);
    }
    for(int &x : b) {
        cin >> x;
        if(x <= kev) x = 1e9 + 1;
    }

    sort(b.rbegin(), b.rend());

    vector<int> ranks(m);
    int p = 0;
    sort(better.rbegin(), better.rend());
    // cout << "better : " << better << '\n';
    for(int i = 0; i < m; i++) {
        while(p < better.size() && better[p] >= b[i] && kev < b[i]) {
            p++;
        }
        // cout << "p : " << p << '\n';
        ranks[i] = p + 1;
    }

    // cout << "ranks : " << ranks << '\n';

    for(int k = 1; k <= m; k++) {
        ll res = 0;
        for(int i = k; i <= m; i += k) {
            res += ranks[i-1];
        }
        cout << res << " \n"[k == m];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}