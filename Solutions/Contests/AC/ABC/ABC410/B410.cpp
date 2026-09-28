#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        int b;
        if(x) {
            b = x - 1;
        } else {
            int lo = *min_element(a.begin(), a.end());
            for(int j = 0; j < n; j++) {
                if(a[j] == lo) {
                    b = j;
                    break;
                }
            }
        }
        a[b]++;
        cout << b + 1 << " \n"[i == q - 1];
    }

    return 0;
}
