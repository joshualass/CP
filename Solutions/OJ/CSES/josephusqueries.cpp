#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    int lz = __builtin_clz(n);
    int rem = n - (1 << (31-lz));
    cout << "n: " << n << " lz: " << lz << " rem: " << rem << "\n";
    if(k <= rem) {
        cout << k * 2 << "\n";
    } else {
        
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}