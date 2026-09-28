#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    string str; cin >> str;

    int logocnt = 0;
    int logowashed = 0;
    int plaincnt = m;
    int plainwashed = m;

    for(int i = 0; i < n; i++) {
        if(str[i] == '0') {
            logowashed = logocnt;
            plainwashed = plaincnt;
        } else if(str[i] == '1') {
            if(plainwashed != 0) {
                plainwashed--;
            } else if(logowashed != 0) {
                logowashed--;
            } else {
                logocnt++;
            }
        } else if(str[i] == '2') {
            if(logowashed != 0) {
                logowashed--;
            } else {
                logocnt++;
            }
        }
    }
    cout << logocnt << '\n';
    return 0;
}