#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    
    auto is_a = [](vector<int> a) -> bool {
        for(int i = 2; i < a.size(); i++) {
            if(a[i] - a[i-1] != a[i-1] - a[i-2]) return 0;
        }
        return 1;
    };
    vector<int> a(n);
    for(int &x : a) cin >> x;
    if(is_a(a)) {
        cout << "arithmetic\n";
        return;
    }
    sort(a.begin(), a.end());
    if(is_a(a)) {
        cout << "permuted arithmetic\n";
        return;
    }
    cout << "non-arithmetic\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}