#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef __int128_t lll;
using namespace std;

lll binexp(lll base, lll power, lll MOD = 1e9 + 7) {
    lll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base;
        }
        base = base*base;
        
        power >>= 1;
    }
    return ans;
}

lll calcNodes(int depth, lll k) {
    return (binexp(k, depth) - 1) / (k - 1);
}

void solve() {
    ll N; cin >> N;
    lll n = N;
    int depth = 3;
    bool flag = false;
    while(calcNodes(depth,2) <= n) {
        lll l = 2;
        lll r = 2;
        lll inc = 2;
        while(calcNodes(depth, r + inc) <= n) {
            r += inc;
            inc += inc;
        }
        while(inc != 0) {
            if(calcNodes(depth, r + inc) <= n) {
                r += inc;
            }
            inc /= 2;
        }

        while(l != r) {
            lll m = (l + r) / 2;
            if(l == m) {
                if(calcNodes(depth,m) < n) {
                    l = r;
                } else {
                    r = l;
                }
            } else {
                if(calcNodes(depth,m) < n) {
                    l = m;
                } else {
                    r = m;
                }
            }
        }
        if(calcNodes(depth,l) == n) {

        // cout << "depth: " << depth << " l: " << l << " r: " << r << "\n";
            flag = true;
            break;
        }
        // cout << "depth? " << depth << "\n";
        depth++;
    }
    cout << (flag ? "YES" : "NO") << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}