
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int cnt = 0;
    for(int i = 1; i <= 12; i++) {
        string s; cin >> s;
        if(s.size() == i) cnt++;
    }

    cout << cnt << '\n';

    return 0;
}