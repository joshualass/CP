#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<int> good;

    int c = 2018 * 12 + 3;
    for(int i = 0; i < 100000; i++) good.insert(c / 12), c += 26;

    int y; cin >> y;
    cout << (good.count(y) ? "yes" : "no") << '\n';

    return 0;
}