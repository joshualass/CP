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

void solve() {
    
    int n, x, y; cin >> n >> x >> y;
    x--;
    y--;

    auto check = [&](vector<int> c) -> bool {
        // cout << "c : " << c << endl;
        for(int i = 0; i < n; i++) {
            vector<int> nei;
            nei.push_back(c[(i + n - 1) % n]);
            nei.push_back(c[(i + 1) % n]);
            if(i == x) nei.push_back(c[y]);
            if(i == y) nei.push_back(c[x]);
            int res = 0;
            while(count(nei.begin(), nei.end(), res)) {
                res++;
            }
            if(c[i] != res) {
                return 0;
            }
        }
        // cout << "good!" << endl;
        return 1;
    };

    vector<int> res;

    vector<int> c(n);
    for(int i = 0; i < n; i++) {
        c[(i + x + 1) % n] = i & 1;
    }

    if(check(c)) res = c;
    
    int t = c[x];
    c[x] = 2;
    if(check(c)) res = c;
    c[x] = t;

    c[y] = 2;
    if(check(c)) res = c;

    assert(!res.empty());
    cout << res << '\n';
    // cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}