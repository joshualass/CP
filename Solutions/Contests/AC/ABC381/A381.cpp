#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    if(s.size() % 2 == 0) {
        cout << "No\n";
        return 0;
    }

    int z = s.size() / 2;
    int ok = 1;
    for(int i = 0; i < z; i++) {
        if(s[i] != '1') ok = 0;
    }
    if(s[z] != '/') ok = 0;
    for(int i = z + 1; i < z * 2 + 1; i++) {
        if(s[i] != '2') ok = 0;
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}