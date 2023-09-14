#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ld calcArea(ld base, ld height) {
    return base * height / 2;
}

void solve() {
    ld n, d, h; cin >> n >> d >> h;
    ld area = 0;
    area += calcArea(d,h) * n;
    ld prevheight; cin >> prevheight;
    for(ld i = 1; i < n; i++) {
        ld newheight; cin >> newheight;
        if(newheight - prevheight < h) {
        ld ratio = (h - (newheight - prevheight)) / h;
        ld overlap = calcArea(d * ratio, h * ratio);
        area -= overlap;
        }
        prevheight = newheight;
    }
    cout << fixed << setprecision(10) << area << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}