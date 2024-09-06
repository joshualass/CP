#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int isok(string &s) {

    for(int i = 1; i < s.size() - 1; i++) {
        if(s[i-1] == s[i+1] && s[i] != s[i+1]) {
            return 0;
        }
    }

    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int length = 1; length <= 10; length++) {
        int cnt = 0;
        for(int i = 0; i < 1 << length; i++) {
            string s = "";
            for(int k = 0; k < length; k++) {
                if((i >> k) & 1) {
                    s.push_back('1');
                } else {
                    s.push_back('0');
                }
            }
            cnt += isok(s);
        }
        cout << cnt << '\n';
    }

    return 0;
}