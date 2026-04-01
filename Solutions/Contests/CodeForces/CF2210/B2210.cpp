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
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        p[i]++;
        if(a[i] > i) {
            p[a[i]]--;
        }
    }

    // cout << "p : " << p << endl;

    int res = 0, cur = 0;
    for(int x : p) {
        cur += x;
        res = max(res, cur);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}