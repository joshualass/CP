#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    array<int,16> a = {};
    int n, q; cin >> n >> q;
    auto work = [&]() -> int {
        //try making making all n
        int ok = 1;
        for(int i = 0; i < 16; i++) {
            if(__builtin_popcount(i) & 1) {
                if(a[i]) ok = 0;
            }
        }
        if(a[10] != a[5]) ok = 0;
        if(ok) return n;
        int res = 0;
        for(int i = 0; i < 16; i++) {
            if(__builtin_popcount(i) % 2 == 0) {
                res += a[i];
            }
        }
        return res;
    };

    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        a[b[i]]++;
    }

    cout << work() << " ";
    for(int qq = 0; qq < q; qq++) {
        int p, x; cin >> p >> x;
        p--;
        a[b[p]]--;
        b[p] = x;
        a[b[p]]++;
        cout << work() << " ";
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}