#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        m[a[i]]++;
    }

    int resl = -1, resr = -1;
    int cl = -1;
    for(int i = 0; i < n; i++) {
        if(m[a[i]] == 1) {
            if(i - cl >= resr - resl) {
                resl = cl, resr = i;
            }
        } else {
            cl = i;
        }
    }

    if(resr == -1) {
        cout << "0\n";
    } else {
        cout << resl + 2 << " " << resr + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}