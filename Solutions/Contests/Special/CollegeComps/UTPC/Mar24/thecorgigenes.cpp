#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ans = 0;
    string s; cin >> s;
    for(int length = 1; length <= 52; length++) {
        for(int i = 0; i + length <= s.size(); i++) {
            vector<int> v(26);
            string curr {};
            for(int j = i; j < i + length; j++) {
                curr += s[j];
                v[s[j] - 'a']++;
            }
            string rev = curr;
            reverse(rev.begin(), rev.end());
            ans += rev == curr && count(v.begin(),v.end(),0) + count(v.begin(),v.end(),1) + count(v.begin(),v.end(),2) == 26;
        }
    }
    cout << ans << '\n';
    return 0;
}