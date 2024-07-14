#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool isright(vector<array<int,2>> a, int origin, int b, int c) {

    a[b][0] -= a[origin][0];
    a[b][1] -= a[origin][1];
    a[c][0] -= a[origin][0];
    a[c][1] -= a[origin][1];

    //right when dot product is 0 :))))
    return a[b][0] * a[c][0] + a[b][1] * a[c][1] == 0;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<array<int,2>> a(3);
    for(auto &x : a) cin >> x[0] >> x[1];

    bool res = 0;
    res |= isright(a,0,1,2);
    res |= isright(a,0,2,1);
    res |= isright(a,1,0,2);
    res |= isright(a,1,2,0);
    res |= isright(a,2,0,1);
    res |= isright(a,2,1,0);

    cout << (res ? "Yes" : "No") << '\n';

    return 0;
}