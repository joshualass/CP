#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll binexp(ll base, ll power, ll MOD = 1e9 + 7) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base;
        }
        if(base*base < base) {
            return -1;
        }
        base = base*base;
        
        power >>= 1;
    }
    return ans;
}

ll calcNodes(int depth, ll k) {

    ll binex = binexp(k,depth);
    if(binex == -1) {
        ll sum = 0;
        ll add = 1;
        for(int i = 0; i <= depth; i++) {
            if(sum + add < sum) {
                return -1;
            }
            sum += add;
            if(i != depth && add < add * k) {
                return -1;
            }
            add *= k;
        }

        return sum;
        // return -1;
    } else {
        return (binex - 1) / (k - 1);
    }
}

void solve() {
    ll n; cin >> n;
    int depth = 3;
    bool flag = false;
    while(calcNodes(depth,2) <= n && calcNodes(depth,2) != -1) {
        ll l = 2;
        ll r = 2;
        ll inc = 2;
        while(calcNodes(depth, r + inc) != -1) {
            r += inc;
            inc += inc;
        }
        while(inc != 0) {
            if(calcNodes(depth, r + inc) != -1) {
                r += inc;
            }
            inc /= 2;
        }

        while(l != r) {
            ll m = (l + r) / 2;
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