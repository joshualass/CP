#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int range_intersect(int l1, int r1, int l2, int r2) {
    int cnt = 0;
    if(r2 > l1 && r2 <= r1) cnt++;
    if(l2 >= l1 && l2 < r1) cnt++;
    swap(l1,l2);
    swap(r1,r2);
    if(r2 > l1 && r2 <= r1) cnt++;
    if(l2 >= l1 && l2 < r1) cnt++;
    return cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c, d, e, f, g, h, i, j, k ,l; cin >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l;

    int poss = 0;

    if(range_intersect(a,d,g,j)) poss++;
    if(range_intersect(b,e,h,k)) poss++;
    if(range_intersect(c,f,i,l)) poss++;

    cout << (poss == 3? "Yes" : "No") << '\n';

    return 0;
}