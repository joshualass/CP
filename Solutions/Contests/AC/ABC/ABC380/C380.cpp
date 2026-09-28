#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    string s; cin >> s;
    int cnt = 0;
    int l = -1, r = n;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0' && i && s[i-1] == '1') {
            cnt++;
        }
        if(l == -1 && cnt == k - 1) {
            l = i;
        }
        if(r == n && cnt == k) {
            r = i;
        }
    }
    // cout << "l : " << l << " r : " << r << '\n';
    reverse(s.begin() + l, s.begin() + r);
    cout << s << '\n';

    return 0;
}