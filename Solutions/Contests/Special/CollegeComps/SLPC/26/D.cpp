#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    vector<vector<int>> res;
    auto op = [&](vector<int> bm) -> void {
        assert(count(bm.begin(), bm.end(), 1) == n / 2);
        auto sv = [&](vector<int> &v) -> void {
            vector<int> t;
            for(int i = 0; i < n; i++) {
                if(bm[i]) t.push_back(v[i]);
            }
            sort(t.begin(), t.end());
            int p = 0;
            for(int i = 0; i < n; i++) {
                if(bm[i]) v[i] = t[p++];
            }
        };
        sv(a);
        sv(b);
        vector<int> o;
        for(int i = 0; i < n; i++) {
            if(bm[i]) o.push_back(i);
        }
        res.push_back(o);
    };

    for(int lo = 0; lo < n / 2; lo += n / 8) {
        int hi = lo + n / 8;
        vector<int> bm(n);
        int cnt = 0;
        for(int j = lo; j < n; j++) {
            if(j < hi || a[j] < hi || b[j] < hi) {
                bm[j] = 1;
                cnt++;
            }
        }
        for(int j = lo; j < n; j++) {
            if(cnt < n / 2 && bm[j] == 0) {
                bm[j] = 1;
                cnt++;
            }
        }
        op(bm);
    }

    vector<int> bm(n);
    for(int i = n / 2; i < n; i++) bm[i] = 1;
    op(bm);

    cout << sz(res) << '\n';
    for(auto x : res) {
        for(int i = 0; i < n / 2; i++) cout << x[i] + 1 << " \n"[i == n / 2 - 1];
    }

    return 0;
}
