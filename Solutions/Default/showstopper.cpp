#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int &x: a) cin >> x;
        for(int &x: b) cin >> x;
        bool flag = false;
        for(int i = 0; i < n; i++) {
            if(min(a[i],b[i]) > min(a[n-1],b[n-1]) || max(a[i],b[i]) > max(a[n-1],b[n-1])) {
                flag = true;
            }
        }
        cout << (flag ? "No" : "Yes") << '\n';
    }

    return 0;
}