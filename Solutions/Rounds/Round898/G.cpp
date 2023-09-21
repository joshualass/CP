#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    string str; cin >> str;
    bool B = false;
    int acnt = 0;
    int smalla = str.size();
    int curra = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == 'A') {
            acnt++;
            curra++;
        } else {
            smalla = min(smalla, curra);
            curra = 0;
            B = true;
        }
    }
    smalla = min(smalla,curra);
    cout << acnt - smalla << "\n";
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}