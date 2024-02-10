#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string ans = "";
    vector<int> cnts(26);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        for(int j = 0; j < 26; j++) {
            if(cnts[j] == num) {
                ans.push_back(j + 'a');
                cnts[j]++;
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