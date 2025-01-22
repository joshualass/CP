#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string a, b, c; cin >> a >> b >> c;
    map<char,int> m;
    for(int i = 0; i < b.size(); i++) {
        m[b[i]] = i;
    }
    int num = 0;
    for(int i = 0; i < a.size(); i++) {
        num *= b.size();
        num += m[a[i]];
    }
    string res = "";
    while(num) {
        res.push_back(c[num % c.size()]);
        num /= c.size();
    }
    reverse(res.begin(), res.end());
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}