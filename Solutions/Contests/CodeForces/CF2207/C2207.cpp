#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, h; cin >> n >> h;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    set<int> hs(a.begin(), a.end());
    hs.insert(h);

    vector<map<int,ll>> work(n);
    vector<ll> all(n);

    for(int i = 0; i < n; i++) {
        int l = i, r = i;
        ll area = 0;
        int prev_height = 0;
        // cout << "i : " << i << endl;
        for(int height : hs) {
            while(l && a[l-1] < height && a[l] < height) l--;
            while(r < n && a[r] < height) r++;
            area += 1LL * (height - prev_height) * (r - l);
            prev_height = height;
            work[i][height] = area;
            // cout << "height : " << height << " area here : " << area << endl;
        }
        all[i] = area;
    }

    // cout << "all : " << all << endl;

    ll res = *max_element(all.begin(), all.end());

    for(int i = 0; i + 1 < n; i++) {
        int mx = a[i+1];
        for(int j = i + 2; j < n; j++) {
            if(mx > a[j]) {
                res = max(res, all[i] + work[j][mx]);
            }
            mx = max(mx, a[j]);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}