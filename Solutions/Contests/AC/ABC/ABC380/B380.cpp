#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int cnt = 0;
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == '-') {
            cnt++;
        } else {
            cout << cnt << " ";
            cnt = 0;
        }
    }

    return 0;
}