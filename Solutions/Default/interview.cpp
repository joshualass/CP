#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        // vector<int> v(n);
        vector<ll> prefix(n+1);
        for(int i = 1; i <= n; i++) {
            int num; cin >> num;
            prefix[i] = prefix[i-1] + num;
        }
        int l = 1; int r = n;
        while(l != r) {
            int m = (l + r) / 2;
            string out = "? " + to_string(m - l + 1);
            for(int i = l; i <= m; i++) {
                out += " " + to_string(i);
            }
            cout << out << endl;
            ll ans; cin >> ans;
            if(prefix[m] - prefix[l-1] == ans) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        cout << "! " << l << endl;
    }

    return 0;
}