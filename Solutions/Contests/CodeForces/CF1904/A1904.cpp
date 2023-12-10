#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool poss(int x, int y, int a, int b, int targx, int targy) {
    int cnt = 0;
    cnt += (bool) (x - a == targx && y - b == targy);
    cnt += (bool) (x + a == targx && y - b == targy);
    cnt += (bool) (x - a == targx && y + b == targy);
    cnt += (bool) (x + a == targx && y + b == targy);
    cnt += (bool) (x - b == targx && y - a == targy);
    cnt += (bool) (x + b == targx && y - a == targy);
    cnt += (bool) (x - b == targx && y + a == targy);
    cnt += (bool) (x + b == targx && y + a == targy);
    return (bool) cnt;
}

void solve() {
    int a, b; cin >> a >> b;
    int xk, yk, xq, yq; cin >> xk >> yk >> xq >> yq;
    int cnt = 0;
    
    cnt += poss(xk + b, yk + a, a, b, xq, yq);
    cnt += poss(xk + a, yk - b, a, b, xq, yq);
    cnt += poss(xk - b, yk - a, a, b, xq, yq);
    cnt += poss(xk - a, yk + b, a, b, xq, yq);
    
    if(a != 0 && b != 0 && a != b) {
        cnt += poss(xk + a, yk + b, a, b, xq, yq);
        cnt += poss(xk - a, yk - b, a, b, xq, yq);
        cnt += poss(xk + b, yk - a, a, b, xq, yq);
        cnt += poss(xk - b, yk + a, a, b, xq, yq);
    }
    cout << cnt << '\n';

    // if(a == b && abs(xk - xq) == a * 2 && abs(yk - yq) == a * 2) {
    //     cout << "1\n";
    // } else {
    //     //check if it's possible
    //     int smalldiff = abs(xk - xq);
    //     int bigdiff = abs(yk - yq);
    //     if(smalldiff > bigdiff) swap(smalldiff, bigdiff);
    //     if(a > b) swap(a,b);
    //     if((a + b == smalldiff && a + b == bigdiff) || (smalldiff == 0 && (bigdiff == a * 2 || bigdiff == b * 2))) {
    //         cout << "2\n";
    //     } else {
    //         cout << "0\n";
    //     }
    // }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}