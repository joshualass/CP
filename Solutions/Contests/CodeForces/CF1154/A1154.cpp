#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> e(4);
    for(int &x : e) cin >> x;
    sort(e.begin(), e.end());
    int a = e[0];
    int b = e[1];
    int c = e[2];
    int d = e[3];
    cout << d - c << " " << d - b << " " << d - a << '\n';

    return 0;
}
