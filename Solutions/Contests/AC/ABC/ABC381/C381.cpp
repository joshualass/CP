#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    int res = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '/') {
            int l = 1;
            while(i - l >= 0 && i + l < n && s[i-l] == '1' && s[i+l] == '2') l++;
            res = max(res, l * 2 - 1);
        }
    }

    cout << res << '\n';

    return 0;
}