#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int l, s; cin >> l >> s;

    string ans = "";
    for(int i = 0; i < l; i++) {
        ans.push_back('*');
    }
    bool poss = 1;

    for(int i = 0; i < s; i++) {
        int start_idx; cin >> start_idx;
        string str; cin >> str;
        start_idx--;
        for(int j = 0; j < str.size(); j++) {
            if(str[j] == '*') break;
            if(ans[j + start_idx] == '*' || ans[j + start_idx] == str[j]) {
                ans[j + start_idx] = str[j];
            } else {
                poss = 0;
                break;
            }
        }
        for(int j = str.size() - 1; j >= 0; j--) {
            if(str[j] == '*') break;
            if(ans[ans.size() - 1 - (str.size() - j - 1)] == '*' || ans[ans.size() - 1 - (str.size() - j - 1)] == str[j]) {
                ans[ans.size() - 1 - (str.size() - j - 1)] = str[j];
            } else {
                poss = 0;
                break;
            }
        }
    }
    if(ans.find('*') != string::npos) poss = 0;
    if(poss) {
        for(auto x : ans) {
            if(x == '*') {
                cout << 'a';
            } else {
                cout << x;
            }
        }
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}