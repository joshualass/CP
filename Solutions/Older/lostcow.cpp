#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    freopen("lostcow.in","r",stdin);
    freopen("lostcow.out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x, y;
    cin >> x >> y;
    int fact = 0;
    ll ans = 0;
    while(true) {
        if(fact % 2 == 0 && y >= x) {
            if(pow(2,fact) >= y-x) {
                ans = y-x;
//                cout << ans << " ";
                for(int i = 0; i < fact; i++) {
                    ans += pow(2,i+1);
                }
                break;
            }
        } 
        if(fact % 2 == 1 && y <= x) {
            if(pow(2,fact) >= x-y) {
                ans = x-y;
                for(int i = 0; i < fact; i++) {
                    ans += pow(2, i+1);
                }
                break;
            }
        }
        fact++;
    }
    cout << ans << "\n";
    return 0;
}