#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;

    auto ask = [&](int x) -> int {
        cout << "? " << x + 1 << endl;
        int res; cin >> res;
        return res - 1;
    };

    vector<int> a(k), b(k);

    for(int i = 0; i < k; i++) {
        a[i] = ask(i);
        b[i] = ask(n - k + i);
    }

    int rot = (k - n % k) % k;
    rotate(b.begin(), b.begin() + rot, b.end());

    // cout << "a : " << a << " b : " << b << endl;

    int l = k, r = n - k;
    while(l != r) {
        int m = (l + r) / 2;
        int f = -1;
        for(int i = 0; i < k; i++) {
            if(a[(m - i) % k] != b[(m - i) % k]) {
                f = m - i;
                break;
            }
        }
        // cout << "l : " << l << " r : " << r << " m : " << m << " f : " << f << endl;
        if(f == -1) {
            l = m + 1;
        } else {
            int val = ask(f);
            if(val == a[f % k]) {
                l = m + 1;
            } else {
                r = m;
            }
        }
    }

    // cout << "l : " << l << endl;

    if(a[(l - 1) % k] == b[(l - 1) % k] && l - 1 >= k) {
        cout << "! -1" << endl;
    } else {
        cout << "! " << l << " " << n - l << endl;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}