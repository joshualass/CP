#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 5;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    for(int i = 1; i < n; i++) {
        swap(a[i-1],a[i]);
        if(is_sorted(a.begin(),a.end())) {
            cout << "Yes\n";
            return 0;
        }
        swap(a[i-1],a[i]);
    }

    cout << "No\n";

    return 0;
}