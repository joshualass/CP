#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

map<char,int> m;

void solve() {
    string s; cin >> s;
    int largest = 0;
    int sum = 0;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(m[s[i]] < largest) {
            sum -= m[s[i]];
        } else {
            sum += m[s[i]];
        }
        largest = max(largest, m[s[i]]);
    }
    cout << sum << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    m['I'] = 1;
    m['V'] = 5;
    m['X'] = 10;
    m['L'] = 50;
    m['C'] = 100;
    m['D'] = 500;
    m['M'] = 1000;

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}