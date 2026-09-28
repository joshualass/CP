#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;

    string ans = "";

    for(int i = 0; i < str.size(); i++) {
        ans.push_back(str[i]);
        if(ans.size() >= 3) {
            if(ans.substr(ans.size()-3) == "ABC") {
                ans.pop_back();ans.pop_back();ans.pop_back();
            }
        }
    }
    cout << ans << '\n';
    return 0;
}