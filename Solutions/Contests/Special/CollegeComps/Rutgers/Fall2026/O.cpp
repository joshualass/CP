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
    
    int n, m; cin >> n >> m;
    // vector<int> a(m, 1);
    // for(int i = 0; i < n; i++) cout << a << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x = 1;
            if(i == 0 && j == 0) x = 6;
            cout << x << " ";
        }
        cout << '\n';
    }

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