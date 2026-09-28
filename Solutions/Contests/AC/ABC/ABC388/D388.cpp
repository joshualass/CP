#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> p(n + 1);
    int c = 0;
    for(int i = 0; i < n; i++) {
        c -= p[i];
        a[i] += c;
        int r = min(i + a[i], n - 1);
        a[i] -= r - i;
        p[r+1]++;
        c++;
    }    

    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }

    return 0;
}