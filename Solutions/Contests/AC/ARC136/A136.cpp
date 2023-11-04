#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    string str; cin >> str;

    string updstr = "";

    for(int i = 0; i < n; i++) {
        if(str[i] == 'A') {
            updstr.push_back('B');
            updstr.push_back('B');
        } else {
            updstr.push_back(str[i]);
        }
    }

    string ans = "";

    for(int i = 0; i < updstr.size(); i++) {
        if(i != updstr.size()-1 && updstr[i+1] == 'B' && updstr[i] == 'B') {
            ans.push_back('A');
            i++;
        } else {
            ans.push_back(updstr[i]);
        }
    }

    cout << ans << '\n';

    return 0;
}