#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b; cin >> a >> b;
    if(a > b) swap(a, b);
    
    cout << (b % 2 ? 1 : 2) << '\n';

    return 0;
}
