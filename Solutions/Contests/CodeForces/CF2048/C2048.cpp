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
    string s; cin >> s;
    int n = s.size();
    array<int,2> a = {1, n};
    vector<int> best(n);
    for(int r = 0; r < n; r++) { //index of the end
        vector<int> c(n);
        for(int l = 0; l < n - r - 1; l++) {
            c[l] = s[l] != '0';
        }
        // cout << "r : " << r << " c0 : " << c << '\n';
        int sb = -1;
        for(int l = 0; l <= r; l++) {
            if(s[n-r+l-1] == '0' && s[l] == '1' && sb == -1) {
                sb = l;
            }
            if(sb == -1) {
                c[n - r + l - 1] = s[n - r + l - 1] != '0';
            } else {
                c[n - r + l - 1] = s[n - r + l - 1] != s[l];
            }
        }
        if(sb == -1) {
            sb = r;
        }
        if(c > best) {
            best = c;
            a = {sb + 1, r + 1};
        }
        // cout << "r : " << r << " c : " << c << '\n';
    }
    cout << 1 << " " << n << " " << a[0] << " " << a[1] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}