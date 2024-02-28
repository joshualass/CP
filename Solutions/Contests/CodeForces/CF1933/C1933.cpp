#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int pw(int a, int i) {
    int ans = 1;
    while(i--) {
        ans *= a;
    }
    return ans;
}

void solve() {
    int a, b, l; cin >> a >> b >> l;
    int ans = 0;
    set<int> s;
    for(int i = 0; l % pw(a, i) == 0; i++) {
        for(int j = 0; l % (pw(a,i) * pw(b,j)) == 0; j++) {
            s.insert(pw(a,i) * pw(b,j));
        }
    }
    cout << s.size() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}