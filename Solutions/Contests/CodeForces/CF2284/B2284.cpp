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
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int mx = *max_element(a.begin(), a.end());
    int mxcnt = count(a.begin(), a.end(), mx);
    if(mxcnt > k) {
        cout << "NO\n";
        return;
    } 

    sort(a.begin(), a.end());
    cout << "YES\n";
    rotate(a.begin(), a.begin() + n - k, a.end());
    reverse(a.begin() + k, a.end());
    cout << a << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}