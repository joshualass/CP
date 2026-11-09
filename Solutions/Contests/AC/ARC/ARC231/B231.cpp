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
    
    int A, B, C; cin >> A >> B >> C;
    vector<int> a(A), b(B);
    iota(a.begin(), a.end(), 0);
    iota(b.begin(), b.end(), 0);
    vector<int> vis(C);
    for(int x : a) {
        for(int y : b) {
            int z = x ^ y;
            if(z < C) vis[z] = 1;
        }
    }
    a.push_back(1024);
    for(int i = 0; i < C; i++) {
        if(vis[i] == 0) {
            b.push_back(1024 + i);
        }
    }
    int ok = 1;
    for(int x : a) {
        for(int y : b) {
            if((x ^ y) == C) {
                // cout << "x : " << x << " y : " << y << endl;
                ok = 0;
            }
        }
    }

    if(ok) {
        cout << "Yes" << '\n';
    } else {
        cout << "No\n";
        return;
    }

    cout << sz(a) << " " << a << '\n';
    cout << sz(b) << " " << b << '\n';

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