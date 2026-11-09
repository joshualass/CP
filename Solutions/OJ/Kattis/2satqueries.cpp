#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    
    int n; cin >> n;
    vector<int> a(4);
    iota(a.begin(), a.end(), 0);
    shuffle(a.begin(), a.end(), rng);

    auto ask = [&](int x, int y, int p1, int p2) -> int {
        x++; y++;
        if(p1) x *= -1;
        if(p2) y *= -1;
        cout << x << " " << y << endl;
        char c; cin >> c;
        return c == 'T';
    };

    vector<int> res(n);
    int id = 3;
    for(int i = 0; i < 3; i++) {
        int p1 = a[i] & 1;
        int p2 = (a[i] >> 1) & 1;
        if(ask(0, 1, p1, p2) == 0) {
            id = i;
            break;
        }
    }

    for(int i = 0; i < 2; i++) {
        int bit = (a[id] >> i) & 1;
        res[i] = bit;
    }

    for(int i = 2; i < n; i++) {
        res[i] = ask(0, i, res[0], 0);
    }
    for(int x : res) {
        cout << (x ? 'T' : 'F');
    }

    cout << endl;

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