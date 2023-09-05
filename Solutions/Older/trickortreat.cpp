#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

ld maxDistance(ld x, vector<pair<ld,ld>> &v) {
    // ld lo = sqrt((x-v[0].first) * (x-v[0].first) + (v[0].second * v[0].second));
    // ld hi = sqrt((x-v[v.size()-1].first) * (x-v[v.size()-1].first) + (v[v.size()-1].second * v[v.size()-1].second));
    ld m = 0;
    for(int i = 0; i < v.size(); i++) {
        m = max(m, sqrt((x-v[i].first) * (x-v[i].first) + (v[i].second * v[i].second)));
    }
    return m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    while(n != 0) {
        vector<pair<ld,ld>> v(n);
        for(int i = 0; i < n; i++) {
            ld x, y; cin >> x >> y;
            v[i] = {x,abs(y)};
        }
        sort(v.begin(), v.end());

        ld l = -200000, r = 200000;

        while(r-l > 0.0000001) {
            ld lo = maxDistance(l + (r-l)/3, v);
            ld hi = maxDistance(l + (r-l)*2/3,v);
            if(hi > lo) {
                r = l + (r-l)*2/3;
            } else {
                l = l + (r-l)/3;
            }
        }

        cout << fixed << setprecision(10) << l << " " << maxDistance(l,v) << '\n';
        cin >> n;
    }

    return 0;
}