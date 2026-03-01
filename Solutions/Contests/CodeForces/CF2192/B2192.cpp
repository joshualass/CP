#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    int cnt = count(s.begin(), s.end(), '1');
    char hit;
    if(cnt % 2 == 0) {
        hit = '1';
    } else {
        if(s.size() % 2 == 1) {
            cout << "-1\n";
            return;
        } else {
            hit = '0';
        }
    }
    vector<int> res;
    for(int i = 0; i < n; i++) if(s[i] == hit) res.push_back(i + 1);
    cout << sz(res) << '\n';
    for(int i = 0; i < sz(res); i++) cout << res[i] << " \n"[i == sz(res) - 1];

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}