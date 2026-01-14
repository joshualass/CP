#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int, int> pii;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    vector<ll> a(n); 
    for(ll &x : a) cin >> x;

    sort(a.begin(), a.end());
    vector<ll> p(n + 1);
    for(int i = 0; i < n; i++) {
        p[i+1] = a[i] + p[i];
    }

    for(int i = 0; i < n; i++) {
        int med = (i + n - 1) / 2;
        ll cost = 0;

        cost += (p[n] - p[med]) - (n - med) * a[med];
        cost += (med - i) * a[med] - (p[med] - p[i]);

        cout << cost << '\n';
    }

    return 0;
}