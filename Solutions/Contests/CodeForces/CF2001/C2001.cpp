#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int ask(int a, int b) {
    cout << "? " << a + 1 << " " << b + 1 << endl;
    int x; cin >> x;
    return x - 1;
}

void solve() {
    int n; cin >> n;
    vector<int> res;
    for(int i = 1; i < n; i++) {
        int lo = 0;
        while(1) {
            int m = ask(lo,i);
            if(m == lo) {
                res.push_back(lo);
                res.push_back(i);
                break;
            }
            lo = m;
        }
    }

    cout << "!";
    for(int x : res) {
        cout << " " << x + 1;
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}