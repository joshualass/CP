#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    set<int> know;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        know.insert(x);
    }
    for(int i = 1; i < n; i++) {
        int x; cin >> x;
        know.erase(x);
    }

    cout << *know.begin() << '\n';

    return 0;
}
