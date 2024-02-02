#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k, m; cin >> n >> k >> m;
    string s; cin >> s;
    string no = "";
    set<char> found;

    for(char c : s) {
        found.insert(c);
        if(found.size() == k) {
            no.push_back(c);
            found.clear();
        }
    }
    if(no.size() >= n) {
        cout << "YES\n";
    } else {
        char add = '\0';
        for(int i = 0; i < k; i++) {
            if(found.count('a' + i) == 0) {
                add = 'a' + i;
                break;
            }
        }
        while(no.size() != n) {
            no.push_back(add);
        }
        cout << "NO\n";
        cout << no << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}