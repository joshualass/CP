#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n,1), b(n);
    iota(b.begin(),b.end(), 0);
    int res = 0;
    auto work = [&](int p, int h) -> void {
        a[b[p]]--;
        if(a[b[p]] == 1) res--;
        b[p] = h;
        a[b[p]]++;
        if(a[b[p]] == 2) res++;
    };
    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int p, h; cin >> p >> h;
            work(p-1,h-1);
        } else {
            cout << res << '\n';
        }
    }

    return 0;
}