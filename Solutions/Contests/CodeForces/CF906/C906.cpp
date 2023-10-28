#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    int onecnt = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == '1') onecnt++;
    }

    if((n & 1) || onecnt * 2 != n) {
        cout << "-1\n";
        return;
    }

    int lptr = 0;
    int rptr = n - 1;
    vector<int> ops;
    while(lptr < rptr) {
        if(str[lptr] != str[rptr]) {
            lptr++;
            rptr--;
            continue;
        }
        if(str[lptr] == '0') {
            ops.push_back(rptr + 1);
            str.insert(rptr + 1, "01");
            rptr += 2;
        } else {
            ops.push_back(lptr);
            str.insert(lptr, "01");
            rptr += 2;
        }
        // break;
    }
    // cout << "newstr: " << str << '\n';
    cout << ops.size() << "\n";
    for(auto x : ops) cout << x << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}