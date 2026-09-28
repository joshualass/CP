#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> res;
    for(int i = 0; i < n; i++) {
        int ok = 1;
        for(int j = 0; j < n; j++) {
            if(i != j && abs(a[i] - a[j]) < d) ok = 0;
        }
        if(ok) res.push_back(i + 1);
    }
    
    cout << sz(res) << '\n';
    for(int x : res) cout << x << " ";
    cout << '\n';

    return 0;
}
