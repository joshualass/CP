#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> a = {
        "walk",
        "no",
        "no",
        "no",
        "yes",
        "yes",
        "backwards",
        "seven"
    };
    
    int n; cin >> n;
    cout << a[n - 1] << '\n';

    return 0;
}
