#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string s, t; cin >> s >> t;
    vector<vector<int>> ss(2, vector<int>(26, -1)), tt(2, vector<int>(26, -1));

    auto stuff = [](string &s, vector<vector<int>> &a) -> void {
        for(int i = 0; i < sz(s); i++) {
            int idx = s[i] - 'a';
            if(a[0][idx] == -1) {
                a[0][idx] = i;
            }
            a[1][idx] = i;
        }
    };

    stuff(s, ss);
    stuff(t, tt);

    auto check = [](vector<vector<int>> &a, int first, int second) -> int {
        if(a[0][first] == -1 || a[1][second] == -1) return 0;
        return a[0][first] < a[1][second];
    };

    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            if(check(ss, i, j) && check(tt, i, j)) {
                string res;
                res.push_back((char) (i + 'a'));
                res.push_back((char) (j + 'a'));
                cout << res << '\n';
                return;
            }
        }
    }

    cout << "HENG!\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}