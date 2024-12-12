#include <iostream>
#include <vector>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(1000001,-1);
    for(int &x : a) cin >> x;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        b[x] = i;
    }

    int res = 0;
    int l = 0, r = -1;
    auto getcost = [&](int l, int r) -> int {
        int c = b[a[r%n]] - b[a[l%n]];
        if(c < 0) c += m;
        return c;
    };

    while(r != n * 2 - 1) {
        if(b[a[(r+1)%n]] != -1 && (r <= l || getcost(l,r) + getcost(r,r+1) < m)) {
            r++;
        } else {
            l++;
            r = max(r, l - 1);
        }
        res = max(res, r - l + 1);
    }

    cout << min(n,res) << '\n';

    return 0;
}