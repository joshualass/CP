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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    string s, t; cin >> s >> t;

    if(sz(t) <= sz(s)) {
        vector<int> p(sz(s) - sz(t) + 2);
        for(int i = 0; i + sz(t) <= sz(s); i++) {
            p[i+1] = p[i] + (s.substr(i, sz(t)) == t);
        }
        // cout << "p : " << p << endl;
        for(int qq = 0; qq < q; qq++) {
            int l, r; cin >> l >> r;
            l--;
            r -= sz(t) - 1;
            // cout << "tl : " << l << " tr : " << r << endl;
            cout << (r > l && p[r] - p[l] > 0 ? "Yes" : "No") << '\n';
        }
    } else {
        for(int qq = 0; qq < q; qq++) cout << "No\n";
    }


    return 0;
}
