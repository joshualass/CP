#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> starton(10,1);
    vector<int> startoff(10);

    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        int num; cin >> num;
        for(int bit = 0; bit < 10; bit++) {
            if(c == '|') {
                if((num >> bit) & 1) {
                    starton[bit] = 1;
                    startoff[bit] = 1;
                }
            }
            if(c == '&') {
                if(((num >> bit) & 1) == 0) {
                    starton[bit] = 0;
                    startoff[bit] = 0;
                }
            }
            if(c == '^') {
                if((num >> bit) & 1) {
                    starton[bit] ^= 1;
                    startoff[bit] ^= 1;
                }
            }
        }
    }

    int ansxor = 0;
    int ansor = 0;
    int ansand = 0;

    for(int bit = 0; bit < 10; bit++) {
        int num = starton[bit] * 2 + startoff[bit];
        //num == 0 turn off
        if(num == 1) { //both switch
            ansxor += 1 << bit;
            ansand += 1 << bit;
        }
        if(num == 2) {//only no change
            ansand += 1 << bit;
        }
        if(num == 3) { //both end on. 
            ansor += 1 << bit;
            ansand += 1 << bit;
        }
    }

    cout << 3 << '\n';
    cout << "^ " << ansxor << '\n';
    cout << "| " << ansor << '\n';
    cout << "& " << ansand << '\n';

    return 0;
}