#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;
    int ans = 0;
    for(int i = 0; i < str.size(); i++) {
        for(int j = i; j < str.size(); j++) {
            bool poss = true;
            for(int k = 0; k <= (j - i)/ 2; k++) {
                if(str[k+i] != str[j-k]) poss = false;
            }
            if(poss) {
                ans = max(ans, j-i+1);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}