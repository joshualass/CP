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

    int start = -1;

    for(int i = 0; i < n; i++) {
        if(str[i] == '?') {
            start = i;
        }
    }

    vector<bool> keys(26);

    int lptr = start;
    int rptr = start;

    while(true) {

        // cout << "l: " << lptr << " r: " << rptr << '\n';
        bool progress = false;
        if(lptr == 0 || rptr == n - 1) {
            break;
        }
        if(str[lptr-1] == '.' || str[lptr-1] >= 'a' || keys[str[lptr-1] - 'A'] ) {
            lptr--;
            progress = true;
        }
        if(str[rptr+1] == '.' || str[rptr+1] >= 'a' || keys[str[rptr+1] - 'A'] ) {
            rptr++;
            progress = true;
        }   

        if(str[lptr] >= 'a') {
            // cout << " add key: " << str[lptr] - 'a' << '\n';
            keys[str[lptr] - 'a'] = true;
        } 
        if(str[rptr] >= 'a') {
            keys[str[rptr] - 'a'] = true;
        }     

        if(!progress) {break;}
    }

    cout << (lptr == 0 || rptr == n - 1 ? "YES" : "NO") << '\n';

    return 0;
}