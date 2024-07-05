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

string a, b;
int aa[200000], bb[200000];
vector<int> solve1(int l, int r) {
    l--;
    int n = r - l;
    vector<int> p(n + 1);
    for(int i = 0; i < n; i++) {
        aa[i] = a[i+l] == '1';
        bb[i] = b[i+l] == '1';
    }

    for(int i = 2; i < n; i++) {
        if(aa[i-2] == 0 && aa[i] == 0 ) bb[i-1] = 1;
    }
    
    for(int i = 2; i < n; i++) {
        if(bb[i-2] && bb[i]) aa[i-1] = 1;
    }

    for(int i = 0; i < n; i++) {
        p[i+1] = p[i] + aa[i];
    }
    return p;
}

void solve() {
    int n; cin >> n;
    cin >> a >> b;
    vector<int> p = solve1(1,n);
    int q; cin >> q;

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        if(r - l + 1 <= 4) {
            vector<int> p1 = solve1(l,r);
            // cout << "p1 : " << p1 << '\n';
            cout << p1[r-l+1] << '\n';
        } else {
            vector<int> p1 = solve1(l,l+3);
            vector<int> p2 = solve1(r-3,r);
            l--;
            cout << (p[r-2] - p[l+2]) + p1[2] + (p2[4] - p2[2]) << '\n';
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}