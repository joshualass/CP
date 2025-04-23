#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    vector<int> res(n, -1);
    for(int &x : a) cin >> x;
    int c = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == -1) {
            c = i;
            res[i] = 0;
        }
    }
    int l = -1, h = 1;
    for(int i = *max_element(a.begin(), a.end()); i >= 1; i--) {
        if(i & 1) {
            for(int j = c + 1; j < n; j++) {
                if(a[j] == i) {
                    res[j] = h++;
                }
            }
            for(int j = c - 1; j >= 0; j--) {
                if(a[j] == i) {
                    res[j] = h++;
                }
            }
        } else {
            for(int j = c + 1; j < n; j++) {
                if(a[j] == i) {
                    res[j] = l--;
                }
            }
            for(int j = c - 1; j >= 0; j--) {
                if(a[j] == i) {
                    res[j] = l--;
                }
            }
        }
    }

    int lo = *min_element(res.begin(), res.end());
    for(int i = 0; i < n; i++) {
        cout << res[i] - lo + 1 << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}