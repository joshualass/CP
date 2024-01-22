#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int p, d;
    cin >> p >> d;
    vector<pair<ll, ll>> dist(d, {0, 0});
    for(int i = 0; i < p; i++) {
        int di, a, b;
        cin >> di >> a >> b;
        di --;
        dist[di].first += a;
        dist[di].second += b;
    }
    ld wasted = 0;
    ld tot = 0;
    for(int i = 0; i < d; i++){
        ll va = dist[i].first;
        ll vb = dist[i].second;
        ll req = (va + vb) / 2 + 1;
        ll wa = 0;
        ll wb = 0;
        if(vb >= req) {
            wa = va;
            wb = vb - req;
            cout << "B ";
        }
        else {
            wa = va - req;
            wb = vb;
            cout << "A ";
        }
        cout << wa << " " << wb << "\n";
        wasted += wa - wb;
        tot += va + vb;
    }
    cout << fixed << setprecision(10) << abs(wasted) / tot << "\n";

    return 0;
}