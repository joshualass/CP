#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> cnts(2e5 + 1);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnts[x]++;
    }

    vector<int> p2(2e5 + 1);
    vector<int> p(2e5 + 1);

    for(int i = 0; i <= 2e5; i++) {
        p2[i] = cnts[i] >= 2;
        p2[i] += p2[i-1];
        p[i] = p[i-1] + cnts[i];
    }

    int best_lo = -1, best_hi = -1, best_cnt = -1;

    for(int i = 1; i <= 2e5; i++) {
        if(cnts[i]) {
            int l = i, r = 2e5;
            while(l != r) {
                int m = (l + r + 1) / 2;
                if(p2[m-1]-p2[i] >= m-1-i && cnts[m]) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            if(p[l]-p[i-1] >= best_cnt) {
                best_cnt = p[l] - p[i - 1];
                best_lo = i, best_hi = l;
            }
        }
    }

    cout << best_cnt << '\n';

    for(int i = best_lo; i <= best_hi; i++) {
        cout << i << " ";
        cnts[i]--;
    }

    for(int i = best_hi; i >= best_lo; i--) {
        while(cnts[i]) {
            cout << i << " ";
            cnts[i]--;
        }
    }

    cout << '\n';

    return 0;
}