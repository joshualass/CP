#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num; cin >> num;
    int upnum = num, lonum = num;
    while(upnum % 100 != 99) {
        upnum++;
    }

    while(lonum % 100 != 99 && lonum >= 0) {
        lonum--;
    }

    // cout << "u : " << upnum << " l : " << lonum << '\n';

    if(lonum < 0 || upnum - num <= num - lonum) {
        cout << upnum;
    } else {
        cout << lonum;
    }

    cout << '\n';

    return 0;
}