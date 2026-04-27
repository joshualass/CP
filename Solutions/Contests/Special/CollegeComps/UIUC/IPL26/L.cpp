#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    int plen = 0;
    
    auto ask = [&](int l, int r) -> int {
        if(r - l < plen) assert(0);
        plen = r - l;
        cout << "? " << l + 1 << " " << r << endl;
        int res; cin >> res;
        return res;
    };

    int pr = 0;
    int len = 1;
    while(pr + len < n) {
        int res = ask(pr, pr + len);
        if(res) {
            break;
        }
        pr += len;
        len *= 2;
    }

    // cout << "pr : " << pr << " len : " << len << endl;

    //there is some one in the range after pr of length n
    int lo = pr, hi = min(n - 1, pr + len - 1);

    // cout << "start lo : " << lo << " hi : " << hi << endl;

    while(lo != hi) {
        int m = (lo + hi) / 2;
        // cout << "lo : " << lo << " hi : " << hi << " m : " << m << endl;
        int left = m - len;
        int res = ask(left + 1, m + 1);
        if(res) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }

    cout << "! " << hi + 1 << endl;

    return 0;
}
