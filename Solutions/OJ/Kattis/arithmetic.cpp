#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

string gen_string(string s) {
    // cout << "s : " << s << '\n';
    string a = "";
    int val = 0;
    int mult = 1;
    for(int i = 0; i < 4; i++) {
        val += (s[i] - '0') * mult;
        mult *= 8;
    }
    for(int i = 0; i < 3; i++) {
        int n = val % 16;
        if(n >= 10) {
            a.push_back('A' + n - 10);
        } else {
            a.push_back('0' + n);
        }
        val /= 16;
    }
    // cout << "a : " << a << '\n';
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;
    reverse(str.begin(), str.end());
    while(str.size() % 4 != 0) {
        str.push_back('0');
    }
    reverse(str.begin(), str.end());
    string ans = "";
    while(str.size()) {
        string j = "";
        for(int i = 0; i < 4; i++) {
            j.push_back(str.back());
            str.pop_back();
        }
        j = gen_string(j);
        for(int i = 0; i < 3; i++) {
            ans.push_back(j[i]);
        }
    }
    while(ans.size() > 1 && ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
    return 0;
}