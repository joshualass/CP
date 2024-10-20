#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

int ask(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << endl;
    int res; cin >> res;
    return res;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);

    for(int i = 0; i < n - 1; i++) {
        int res = ask(i,i+1);
        a[i+1] = a[i] ^ res ^ 1;
    }

    // cout << "a : " << a << '\n';

    int l = 0, r = n - 1;
    while(l != r) {
        // cout << "l : " << l << " r : " << r << '\n';
        //case we have entire range. 
        if(l == 0 && r == n - 1) {
            int m = (l + r) / 2;
            int res = ask(m,l);
            if(res ^ 1 == a[l] ^ a[m]) { //not in the range [l,m]
                l = m + 1;
            } else {
                r = m;
            }
        } else if(l != 0) { //case where we can query an extra guy on the left
            int m = (l + r) / 2;
            int res = ask(m,l-1);
            if(res ^ 1 == a[l-1] ^ a[m]) { //not in the range [l-1,m]
                l = m + 1;
            } else {
                r = m;
            }
        } else { //case where r is not at the end, so we can get an extra guy to the right
            int m = (l + r) / 2 + 1;
            int res = ask(r+1,m);
            if(res ^ 1 == a[m] ^ a[r+1]) { //not in range [m,r+1]
                r = m - 1;
            } else {
                l = m;
            }
        }
    }
    
    cout << "! " << l + 1 << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}