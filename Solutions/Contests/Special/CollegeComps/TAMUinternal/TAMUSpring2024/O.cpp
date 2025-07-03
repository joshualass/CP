#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    int sx, sy; cin >> sx >> sy;
    set<pair<int,int>> s;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        int dx = abs(x-sx);
        int dy = abs(y-sy);
        if(dx == 0) {
            s.insert({0,(y-sy)/abs(y-sy)});
        } else if(dy == 0) {
            s.insert({(x-sx)/abs(x-sx),0});
        } else {
            int g = gcd(dx,dy);
            s.insert({(x-sx)/g,(y-sy)/g});
        }
    }
    cout << s.size() << '\n';
    return 0;
}