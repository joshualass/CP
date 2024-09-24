#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int ask(string s) {
    cout << "? " << s << endl;
    int res; cin >> res;
    return res;
}

void solve() {
    int n; cin >> n;

    int s = ask("0");
    if(s == 0) {
        cout << "! " << string(n,'1') << endl;
        return;
    }

    string cur = "0";
    while(cur.size() != n) {
        string add0 = "0" + cur;
        string add1 = "1" + cur;
        
        int r0 = ask(add0);
        int r1 = ask(add1);

        if(r0) {
            cur = "0" + cur;
        } else if(r1) {
            cur = "1" + cur;
        } else {
            break;
        }

    }

    while(cur.size() != n) {
        string add0 = cur + "0";
        int r0 = ask(add0);
        if(r0) {
            cur.push_back('0');
        } else {
            cur.push_back('1');
        }
    }

    cout << "! " << cur << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}