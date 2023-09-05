#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    double tape = 0;
    double add = pow(2, -3.0/ 4);
    ll needed = 2;
    while(n-- > 1) {
        tape += needed / 2 * add;
        ll num;
        cin >> num;
        if(num >= needed) {
            cout << setprecision(10) << fixed << tape;
            return 0;
        }
        needed -= num;
        needed *= 2;
        add /= pow(2,.5);
    }
    cout << "impossible";
    return 0;
}