#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    map<char,int> m;
    set<char> ri(s.begin(), s.end());
    vector<char> r;
    for(int c : ri) {
        int i = m.size();
        m[c] = i;
        r.push_back(c);
    }
    for(int i = 0; i < n; i++) {
        s[i] = r[r.size()-1-m[s[i]]];
    }
    cout << s << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}