#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;

    while (T-- > 0) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int &x : v) cin >> x;

        int l = INT_MAX;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                l = min(l, gcd(v[i],v[j]));
            }
        }
        if(l > 2) {
            cout << "No" << '\n';
        } else {
            cout << "Yes" << '\n';
        }
    }

    return 0;
}