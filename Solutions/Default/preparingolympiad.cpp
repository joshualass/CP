#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, l, r, x;
    cin >> n >> l >> r >> x;
    int total = 0;
    vector<int> v(n);
    for(int& x : v) {
        cin >> x;
    }
    for(int i = 0; i < pow(2,n); i++) {
        int count = 0;
        int least = INT_MAX;
        int most = INT_MIN;
        for(int t = 0; t < n; t++) {
            if(i & (1 << t)) { // i & (1 << t)
                count += v[t];
                least = min(least,v[t]);
                most = max(most,v[t]);
            }
        }
        if(count <= r && count >= l && (most - least) >= x) {
            total++;
        }
    }
    cout << total;
    return 0;
}