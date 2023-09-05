#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ld a, d; cin >> a >> d;
    ld totalTime = 0;
    map<ld,ld> ascent;
    map<ld,ld> descent;
    ld ascentTime = 0;
    ld ascentHeight = 0;
    ascent.insert({0,0});
    for(int i = 0; i < a; i++) {
        ld h, t; cin >> h >> t;
        ascentHeight += h;
        ascentTime += t;
        ascent.insert({ascentTime,ascentHeight});
    }
    ascent.insert({INT_MAX,ascentHeight});
    ld descentTime = 0;
    ld descentHeight = ascentHeight;
    descent.insert({descentTime,descentHeight});
    for(int i = 0; i < d; i++) {
        ld h, t; cin >> h >> t;
        descentTime += t;
        descentHeight -= h;
        descent.insert({descentTime,descentHeight});
    }
    descent.insert({INT_MAX,0});
    // cout << "descents: \n";
    // for(pair<int,int> x : descent) {
    //     cout << x.first << ' ' << x.second << '\n';
    // }

    ld l = 0;
    ld r = min(descentTime,ascentTime);
    while(r - l > 0.0000000001) {
        ld middle = (l + r) / 2;
        pair<ld,ld> lower = *(--ascent.upper_bound(middle));
        pair<ld,ld> upper = *ascent.upper_bound(middle);
        ld ascentPosition = lower.second + (upper.second - lower.second) / (upper.first - lower.first) * (middle - lower.first);

        lower = *(--descent.upper_bound(middle));
        upper = *descent.upper_bound(middle);
        ld descentPosition = lower.second + (upper.second - lower.second) / (upper.first - lower.first) * (middle - lower.first);

        if(descentPosition > ascentPosition) {
            l = middle;
        } else {
            r = middle;
        }
    }
    // if((*(--ascent.upper_bound(l))).second == (*ascent.upper_bound(l)).second && (*(--descent.upper_bound(l))).second == (*descent.upper_bound(l)).second) {
    //     l = (*(--ascent.upper_bound(l))).first;
    // }

    cout << fixed << setprecision(10) << l;

    return 0;
}