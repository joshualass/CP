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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n; cin >> m >> n;
    vector<array<int,2>> a(m);
    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
        }
    }   

    vector<array<int,2>> b(n);
    for(auto &x : b) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    vector<int> c(n);
    for(int &x : c) cin >> x;

    cout << c << '\n';

    return 0;
}