#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    array<string,3> a = {};
    for(auto &x : a) cin >> x;

    vector<string> res;
    auto move = [&](int idx, int dir) -> void {
        //0 CW, 1 CCW
        if(idx <= 2) {
            if(dir) {
                rotate(a[idx].begin(), a[idx].begin() + 9, a[idx].end());
            } else {
                rotate(a[idx].begin(), a[idx].begin() + 1, a[idx].end());
            }
        } else {
            


        }
    };



    return 0;
}
