#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    int sum = 0;
    for(int i = 0 ; i < n-1; i++) {
        int num; cin >> num;
        // cout << "NuM: " << num << " sum: " << sum << "\n";
        sum += num;
    }
    cout << -sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}