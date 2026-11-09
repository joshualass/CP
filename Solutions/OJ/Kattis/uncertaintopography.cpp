#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;

    map<int,char> m;
    int cur = 0;
    m[0] = s[0];
    for(char c : s) {
        if(c == m[cur]) {

        } else if(m.count(cur + 1) && c == m[cur + 1]) {
            cur++;
        } else if(m.count(cur - 1) && c == m[cur - 1]) {
            cur--;
        } else if(m.count(cur + 1) == 0) {
            cur++;
        } else {
            cur--;
        }
        m[cur] = c;
    }

    set<char> res;

    res.insert(m.begin()->second);
    res.insert((--m.end())->second);

    for(char c : res) cout << c;
    cout << '\n';

    return 0;
}
