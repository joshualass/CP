#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ld,2>> a(n);
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }

    auto shoelace = [&](array<ld,2> first, array<ld,2> second) -> ld {
        return first[0] * second[1] - first[1] * second[0];
    };

    ld start = 0;
    for(int i = 0; i < n; i++) {
        start += shoelace(a[i], a[(i + 1) % n]);
    }

    cout << start << '\n';

    ld res = 0;
    
    auto test = [&](array<ld,2> first, array<ld,2> second, array<ld,2> third) -> ld {
        ld starting_area = shoelace(first, second) + shoelace(second, third) + shoelace(third, first);
        starting_area /= 2;
        ld 
    };

    return 0;
}
