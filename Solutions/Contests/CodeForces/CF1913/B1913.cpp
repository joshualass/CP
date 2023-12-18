#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    string str; cin >> str;
    int zerocnt = count(str.begin(), str.end(), '0');
    int onecnt = count(str.begin(), str.end(), '1');

    int ans = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '0') {
            if(onecnt) {
                onecnt--;
            } else {
                ans = str.size() - i;
                break;
            }
        } else if(str[i] == '1') {
            if(zerocnt) {
                zerocnt--;
            } else {
                ans = str.size() - i;
                break;
            }
        }
    }
    cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}