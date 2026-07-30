#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x + 1 << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    for(int &x : b) {
        cin >> x;
        x--;
    }

    vector<array<int,2>> res;

    auto addop = [&](int l, int r) -> void {
        assert(0 <= l && l < r && r <= n && a[l] == a[r - 1]);
        res.push_back({l, r});
        reverse(a.begin() + l, a.begin() + r);
        // cout << "op : " << l << " " << r << endl;
    };

    for(int i = 0; i < n; i++) {
        int nx = b[i];
        if(a[i] != b[i]) {
            if(i == 0) {
                break;
            }
            assert(i > 0);
            vector<int> lo(n, n), hi(n, -1);
            for(int j = i; j < n; j++) {
                lo[a[j]] = min(lo[a[j]], j);
                hi[a[j]] = max(hi[a[j]], j);
            }

            // cout << "lo : " << lo << " hi : " << hi << endl;

            for(int j = i; j < n; j++) {
                if(a[j] == a[i - 1]) {
                    if(a[j-1] == nx) {
                        addop(i - 1, j + 1);
                        assert(a[i] == b[i]);
                        break;
                    } else if(j + 1 < n && a[j+1] == nx) {
                        int f = 0;
                        for(int k = 0; k < n; k++) {
                            if(lo[k] <= j && hi[k] >= j + 1) {
                                int l = lo[k], r = hi[k] + 1;
                                addop(l, r);
                                int nxj = r - 1 - j + l;
                                addop(i - 1, nxj + 1);
                                assert(a[i] == b[i]);
                                f = 1;
                                break;
                            }
                        }
                        if(f) break;
                    }
                }
            }
        }
        // cout << "i : " << i << " a : " << a << endl;
    }

    if(a == b) {
        cout << "YES\n";
        cout << sz(res) << '\n';
        for(auto [l, r] : res) cout << l + 1 << " " << r << '\n';
    } else {
        cout << "NO\n";
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