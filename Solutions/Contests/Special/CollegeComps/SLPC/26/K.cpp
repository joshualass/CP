#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        a[y] = min(a[y], x);
    }
    int lo = n;
    for(int i = n; i >= 0; i--) {
        lo = min(lo, a[i]);
        a[i] = lo;
    }

    ll res = 0, cur = 0;
    vector<array<ll,2>> st; // {len, idx}

    st.push_back({inf, -1});

    auto push_stack = [&](ll len, ll idx) -> void {
        while(len >= st.back()[0]) {
            cur -= 
        }
    };

    for(int i = 1; i <= n; i++) {

        int len = i - a[i];


    }

    return 0;
}
