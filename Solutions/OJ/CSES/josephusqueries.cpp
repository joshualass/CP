#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int base = 1 << (31 - __builtin_clz(n));
    int chop = n - base;
    int res;
    // cout << "k : " << k << '\n';
    // cout << "base : " << base << '\n';
    if(k <= chop) {
        res = k * 2;
    } else {
        k -= chop;
        // cout << "rem k : " << k << '\n';
        int get = 0;
        for(int kill = base / 2, skip = 2; kill; kill /= 2, skip *= 2) {
            if(k <= kill) {
                get = skip * (k - 1) + skip / 2;
                break;
            }
            k -= kill;
        }
        int cur = 1 + chop * 2;
        int after = n - chop * 2;
        // cout << "get : " << get << " cur : " << cur << " after : " << after << '\n';
        if(get < after) {
            res = cur + get;
        } else {
            int left = get - after;
            res = 1 + left * 2;
        }
    }
    
    cout << res << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}