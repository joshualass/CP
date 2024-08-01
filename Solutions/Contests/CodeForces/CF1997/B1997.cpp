#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    string s1, s2; cin >> s1 >> s2;

    int res = 0;

    for(int i = 1; i < n - 1; i++) {
        if(s1[i-1] == 'x' && s1[i] == '.' && s1[i+1] == 'x' && s2[i-1] == '.' && s2[i] == '.' && s2[i+1] == '.') {
            res++;
        }
    }

    swap(s1,s2);

    for(int i = 1; i < n - 1; i++) {
        if(s1[i-1] == 'x' && s1[i] == '.' && s1[i+1] == 'x' && s2[i-1] == '.' && s2[i] == '.' && s2[i+1] == '.') {
            res++;
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}