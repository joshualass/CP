#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    set<int> s;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(a[i]) s.insert(i);
    }

    ll res = 0;
    for(int i = 0; i < n; i++) {
        int n1 = (s.lower_bound(i) == s.end() ? n : *s.lower_bound(i));
        int n2 = (s.upper_bound(n1) == s.end() ? n : *s.upper_bound(n1));
        int n3 = (s.upper_bound(n2) == s.end() ? n : *s.upper_bound(n2));
        if(n2 == n) continue;

        vector<int> b = {a[n1], a[n2]};
        sort(b.begin(), b.end());
        if(b == vector<int>{1, 1} || b == vector<int>{1, 2}) {
            res += n3 - n2 - (n1 == i && n2 == i + 1);
        }
    }

    cout << res << '\n';

    return 0;
}
