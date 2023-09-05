#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<int> v(n);
        for(int &x: v) cin >> x;
        bool flag = false;
        for(int i = 1; i <= n; i++) {
            if(v[i-1] <= i) {
                flag = true;
            }
        }
        cout << (flag ? "YES" : "NO") << "\n";
    }

    return 0;
}