#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;
    if(s[0] == 's') s[0] = '.';
    if(s[n-1] == 'p') s[n-1] = '.';

    int f = 0;

    if(count(s.begin(), s.end(), 'p')) f++;
    if(count(s.begin(), s.end(), 's')) f++;

    cout << (f < 2 ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}