#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<ll> v(n);
        for(ll &x: v) cin >> x;
        sort(v.begin(), v.end());
        ll sum = 1;
        if(v[0] != 1) {
            cout << "NO\n";
            continue;
        }
        bool flag = false;
        for(int i = 1; i < n; i++) {
            if(v[i] > sum) {
                cout << "NO\n";
                flag = true;
                break;;
            }
            sum += v[i];
        }
        if(!flag) {
            cout << "YES\n";
        }
    }

    return 0;
}