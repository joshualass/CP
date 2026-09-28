#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    string s; cin >> s;

    vector<int> nl(n);
    int p = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '/') p = i;
        nl[i] = p;
    }

    // cout << "nl : " << nl << '\n';

    vector<int> p1(n+1), p2(n+1);
    for(int i = 0; i < n; i++) {
        p1[i+1] = p1[i] + (s[i] == '1');
        p2[i+1] = p2[i] + (s[i] == '2');
    }

    // cout << "p1 : " << p1 << " p2 : " << p2 << '\n';

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        int lo = l, hi = r - 1;
        int res = 0;
        while(lo != hi) {
            int m = (lo + hi) / 2;
            int idx = nl[m];
            if(idx < l) {
                lo = m + 1;
            } else {
                int c1 = p1[idx] - p1[l];
                int c2 = p2[r] - p2[idx];
                // cout << "l : " << l << " r : " << r << " m : " << m << " idx : " << idx << " lo : " << lo << " hi : " << hi << " c1 : " << c1 << " c2 : " << c2 << '\n';
                res = max(res, 1 + min(c1,c2) * 2);
                if(c1 > c2) {
                    hi = m;
                } else {
                    lo = m + 1;
                }
            }
        }
        // cout << "lo : " << lo << '\n';
        int idx = nl[lo];
        if(idx < l) {
            cout << "0\n";
        } else {
            int c1 = p1[idx] - p1[l];
            int c2 = p2[r] - p2[idx];
            cout << max(res, 1 + min(c1,c2) * 2) << '\n';
        }
    }

    return 0;
}