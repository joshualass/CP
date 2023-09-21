#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string str; cin >> str;
    int cnt = 0;
    for(int i = 0; i < 3; i++) {
        if(str[i] - (i + 'a') != 0) {
            cnt++;
        }
    }
    cout << (cnt == 3 ? "NO\n" : "YES\n");
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}