#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    int ok = 1;

    auto fill_work = [&]() -> void {
        for(int lo = 0; lo < k; lo++) {
            for(int i = lo + k; i < n; i += k) {
                int here = -1;
                if(a[i] != a[i-k]) {
                    here = a[i];
                } else if(b[i-k] != -1) {
                    here = b[i-k];
                }
                if(here != -1) {
                    if(b[i] == -1) {
                        b[i] = here;
                    } else {
                        if(b[i] != here) {
                            ok = 0;
                        }
                    }
                }
            }
        }
    };

    fill_work();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    fill_work();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;
    // cout << "ok : " << ok << endl;

    multiset<int> ms;
    for(int i = 0; i < k; i++) {
        ms.insert(a[i]);
    }
    for(int i = 0; i < k; i++) {
        if(b[i] != -1) {
            if(ms.count(b[i]) == 0) {
                ok = 0;
            } else {
                ms.erase(ms.find(b[i]));
            }
        }
    }
    
    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}