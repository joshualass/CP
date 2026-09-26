#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    auto oc = [](vector<int> a) -> int {
        int res = 0;
        for(int x : a) res += x & 1;
        return res;
    };

    if(accumulate(a.begin(), a.end(), 0) == accumulate(b.begin(), b.end(), 0) && oc(a) == oc(b) && (oc(a) || a == b)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
