#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k; cin >> n >> k;
    string s; cin >> s;

    vector<int> toggle;
    for(int i = 0; i < n * 2; i++) {
        if(s[i] == '1' && s[(i + 1) % (n * 2)] == '0') {
            toggle.push_back(i);
            toggle.push_back((i + 1) % (n * 2));
        }
    }

    for(int x : toggle) {
        if(s[x] == '0') {
            s[x] = '1';
        } else {
            s[x] = '0';
        }
    }

    array<int,2> res = {};
    for(int i = 0; i < n * 2; i++) {
        if(s[i] == '1') res[i & 1]++;
    }

    cout << res[1] << " " << res[0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}