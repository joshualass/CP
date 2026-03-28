#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 0; i < n; i++) {
        int over = 0, under = 0;
        for(int j = i + 1; j < n; j++) {
            if(a[j] < a[i]) under++;
            if(a[j] > a[i]) over++;
        }
        cout << max(over, under) << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}