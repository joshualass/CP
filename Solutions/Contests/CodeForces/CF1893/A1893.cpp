#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    string str; cin >> str;

    int xposs = 0;
    int yposs = 0;
    
    for(int x = 1; x <= 20; x++) {
        for(int y = 1; y <= 20; y++) {
            int acnt = 0;
            int bcnt = 0;
            int awin = 0;
            int bwin = 0;
            for(int j = 0; j < n; j++) {
                if(str[j] == 'A') {
                    acnt++;
                    if(acnt == x) {
                        awin++;
                        acnt = 0;
                        bcnt = 0;
                    }
                } else if(str[j] == 'B') {
                    bcnt++;
                    if(bcnt == x) {
                        bwin++;
                        bcnt = 0;
                        acnt = 0;
                    }
                }
            }
            if(acnt == 0 && bcnt == 0) {
                if(awin > bwin && awin == y && str.back() == 'A') {
                    // cout << "x: " << x << " y: " << y << " awin\n";
                    xposs++;
                } else if(bwin > awin && bwin == y && str.back() == 'B') {
                    // cout << "x: " << x << " y: " << y << " bwin\n";
                    yposs++;
                }
            }
        }
    }
    // cout << xposs << " " << yposs << '\n';
    if(xposs > 0 && yposs > 0) {
        cout << "?\n";
    } else if(xposs > 0) {
        cout << "A\n";
    } else {
        cout << "B\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}