#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    array<int,2> s, e, t;
    for(auto &x : s) cin >> x;
    for(auto &x : e) cin >> x;
    for(auto &x : t) cin >> x;

    int f = 0;

    auto check1 = [&]() -> void {
        int time = 0;
        time += abs(s[0]);
        time += abs(e[0] - s[0]);
        if(time > t[0]) return;
        time += abs(s[1] - e[0]);
        time += abs(e[1] - s[1]);
        if(time > t[1]) return;
        f = 1;
    };

    auto check2 = [&]() -> void {
        int time = 0;
        time += abs(s[0]);
        time += abs(s[1] - s[0]);
        time += abs(e[1] - s[1]);
        if(time > t[1]) return;
        time += abs(s[1] - e[1]);
        time += abs(e[0] - s[1]);
        if(time > t[0]) return;
        f = 1;
    };

    check1();
    check2();
    
    swap(s[0], s[1]);
    swap(e[0], e[1]);
    swap(t[0], t[1]);

    check1();
    check2();

    cout << (f ? "possible" : "impossible") << '\n';

    return 0;
}
