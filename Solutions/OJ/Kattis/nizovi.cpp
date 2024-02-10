#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    int lo = 0;
    int tabs = 0;

    for(int i = 0; i < s.size(); i++) {
        
    }

    // for(int i = 0; i < s.size(); i++) {
    //     if(s[i] != '}') {
    //         cout << s[i];
    //         if(s[i] == '{') {
    //             cout << '\n';
    //             tabs++;
    //             if(s[i+1] >= 'a' && s[i+1] <= 'z') {
    //                 for(int j = 0; j < tabs; j++) cout << "  ";
    //             }
    //         }
    //         if(s[i] == ',') {
    //             cout << '\n';
    //             for(int j = 0; j < tabs; j++) cout << "  ";
    //         }
    //     } else {
    //         tabs--;
    //         if(s[i-1] >= 'a' && s[i-1] <= 'z' || s[i-1] == '}') cout << '\n';
            
    //         if(i != s.size() - 1) {
    //             for(int j = 0; j < tabs; j++) cout << "  ";
    //         }
    //         cout << s[i];
    //     }
    // }
    // cout << '\n';

    return 0;
}