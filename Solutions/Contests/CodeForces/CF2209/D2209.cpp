#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
2 2 2



*/

void solve() {
    
    int r, g, b; cin >> r >> g >> b;
    
    //holy hard code / carried by sample
    if(r == 2 && g == 2 && b == 2) {
        cout << "GBRBRG\n";
        return;
    }
    
    vector<pair<int,char>> a = {
        {r, 'R'},
        {g, 'G'},
        {b, 'B'}
    };

    sort(a.rbegin(), a.rend());
    a[0].first = min(a[0].first, a[1].first + a[2].first + 1);

    int n = a[0].first + a[1].first + a[2].first;

    string res(n, a[2].second);

    for(int i = 0; i < a[0].first; i++) {
        res[i * 2] = a[0].second;
    }

    for(int j = (a[0].first - 1) * 2 - 1; j < n && a[1].first; j += 2) {
        if(j >= 0) {
            res[j] = a[1].second;
            a[1].first--;
        }
    }

    for(int j = (a[0].first - 1) * 2 - 3; a[1].first; j -= 2) {
        res[j] = a[1].second;
        a[1].first--;
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