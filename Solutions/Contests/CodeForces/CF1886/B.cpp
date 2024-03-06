#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ld dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1 - y2));
}

void solve() {
    ld px,py, ax,ay,bx,by; cin >> px >> py >> ax >> ay >> bx >> by;
    ld dist1 = max(dist(0,0,ax,ay),dist(ax,ay,px,py));
    ld dist2 = max(dist(0,0,bx,by),dist(bx,by,px,py));
    ld dist3 = max({dist(0,0,ax,ay),dist(ax,ay,bx,by)/2,dist(bx,by,px,py)});
    ld dist4 = max({dist(0,0,bx,by),dist(ax,ay,bx,by)/2,dist(ax,ay,px,py)});
    // cout << dist1 << " " << dist2 << " " << dist3 << " " << dist4 << "\n";
    cout << fixed << min({dist1,dist2,dist3,dist4}) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}