#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str = "";

    for(int i = 0; i < 20; i++) {
        str.push_back('a');
    }

    pair<int, string> ans = {20, str};
    for(int i = 0; i < 20; i++) {
        pair<int,string> best = {ans.first, ans.second};
        for(int j = 0; j < 26; j++) {
            str[i] = 'a' + j;
            // cout << "best:" << best << '\n';
            cout << str << endl;
            int num; cin >> num;
            if(num < best.first) {
                best = {num, str};
            }
            if(num == 0) {
                return 0;
            }
        }
        ans = {best.first, best.second};
        str = best.second;
    }

    return 0;
}