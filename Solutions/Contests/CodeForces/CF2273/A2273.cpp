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
    int l = 1, r = n;

    auto work = [&](int test) -> vector<int> {
        vector<int> res;
        int p = 0;
        for(int i = test; i >= 1; i--) {
            int take = min(test, (n - sz(res))) / i;
            for(int j = 0; j < take; j++) {
                p++;
                for(int k = 0; k < i; k++) res.push_back(p);
            }
        }
        return res;
    };

    while(l != r) {
        int m = (l + r) / 2;
        if(sz(work(m)) == n) {
            r = m;
        } else {
            l = m + 1;
        }
    }    

    auto res = work(l);
    cout << l << '\n';
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}