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
    
    int n, m, l; cin >> n >> m >> l;
    vector<int> a(l);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x - 1] = 1;
    }
    vector<int> dangers(m);
    int flashes_left = n;
    int res = 0;
    for(int i = 0; i < l; i++) {
        sort(dangers.rbegin(), dangers.rend());
        int mn_idx = 0;
        for(int j = 1; j < min(m, flashes_left + 1); j++) {
            if(dangers[j] < dangers[mn_idx]) mn_idx = j;
        }
        dangers[mn_idx]++;
        if(a[i]) {
            int mx_idx = 0;
            for(int j = 1; j < m; j++) {
                if(dangers[j] > dangers[mx_idx]) mx_idx = j;
            }
            dangers[mx_idx] = 0;
            flashes_left--;
        }
    }
    
    cout << *max_element(dangers.begin(), dangers.end()) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}