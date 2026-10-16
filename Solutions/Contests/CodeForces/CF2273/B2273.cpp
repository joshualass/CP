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
    vector<int> ops;
    array<int,3> alive = {1,1,1};
    
    for(int i = 0; i < 3; i++) {
        int zap = -1;
        for(int j = 0; j < 3; j++) {
            int here = (j + sz(ops)) % 3;
            if(alive[here]) {
                alive[here] = 0;
                zap = j;
                break;
            }
        }
        for(int j = 2 * n - 4 + zap + 2; j >= 2; j -= 2) ops.push_back(j);
    }

    assert(sz(ops) <= 3 * n);
    cout << sz(ops) << '\n';
    cout << ops << '\n';

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