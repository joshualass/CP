#include <bits/stdc++.h>
using namespace std;

signed main() {
    
    while(1) {
        int x, y; cin >> x >> y;
        double w; cin >> w;
        if(x == 0) break;
        vector<double> a(x), b(y);
        for(double &z : a) cin >> z;
        for(double &z : b) cin >> z;
        auto check = [](double s, double t, vector<double> m, double w) -> bool {
            sort(m.begin(), m.end());
            double p = s;
            for(double x : m) {
                if(x - w / 2 > p) return 0;
                p = x + w / 2;
            }
            return p >= t;
        };
        cout << (check(0, 75, a, w) && check(0, 100, b, w) ? "YES" : "NO") << '\n';
    }

    return 0;
}
