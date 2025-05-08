 #include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;    
    vector<int> a(n);
    for(int &x : a) cin >> x;
    if(*min_element(a.begin(), a.end()) == *max_element(a.begin(), a.end())) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        int mx = *max_element(a.begin(), a.end());
        for(int x : a) {
            if(x == mx) {
                cout << "1 ";
                mx = -1;
            } else {
                cout << "2 ";
            }
        }
        cout << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}