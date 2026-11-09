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
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    vector<int> status(n);
    int cnt = 0;

    auto upd = [&](int idx) -> void {
        cnt -= status[idx];

        int ok = 1;
        if(idx) {
            if(abs(b[idx - 1] - b[idx]) > a[idx] - a[idx - 1]) {
                ok = 0;
            }
        }
        if(idx + 1 < n) {
            if(abs(b[idx + 1] - b[idx]) > a[idx + 1] - a[idx]) {
                ok = 0;
            }
        }

        if(idx && idx + 1 < n) {
            int left = abs((a[idx] - b[idx]) - a[idx - 1]) < b[idx - 1];
            int right = abs((a[idx] + b[idx]) - a[idx + 1]) < b[idx + 1];
            if(left && right) {
                ok = 0;
            }
        }

        status[idx] = ok;
        cnt += status[idx];
    };

    for(int i = 0; i < n; i++) upd(i);

    // cout << "starting status : " << status << endl;
    
    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int p, s; cin >> p >> s;
        p--;
        b[p] = s;
        for(int j = max(0, p - 1); j <= min(n - 1, p + 1); j++) {
            upd(j);
        }
        // cout << "status : " << status << endl;
        cout << (cnt == n ? "Yes" : "No") << '\n';
    }

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