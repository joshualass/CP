#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    int res = 1;

    for(int s = 0; s < n; s++) {

        vector<int> lo(1, a[s]), hi(1, a[s]);

        for(int j = s + 1; j < n; j++) {

            int l = -1, r = hi.size() - 1;
            while(l != r) {
                int m = (l + r + 1) / 2;
                if(hi[m] < a[j]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            l++;
            if(l == hi.size()) {
                hi.push_back(-1);
            } 
            if(l) hi[l] = a[j];

            l = -1, r = lo.size() - 1;
            while(l != r) {
                int m = (l + r + 1) / 2;
                if(lo[m] > a[j]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            l++;
            if(l == lo.size()) {
                lo.push_back(-1);
            }
            if(l) lo[l] = a[j];

        }
        res = max(res, (int) (lo.size() + hi.size()));
    }
    
    cout << res - 1 << '\n';

    return 0;
}
