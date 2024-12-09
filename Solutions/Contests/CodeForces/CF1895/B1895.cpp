#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    
    int n; cin >> n;

    vector<int> v(n * 2);
    for(auto &x: v) cin >> x;

    sort(v.begin(), v.end());

    int score = v[n-1] - v[0] + v[n*2 - 1] - v[n];
    cout << score << '\n';
    for(int i = 0; i < n; i++) {
        cout << v[i] << " " << v[i+n] << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}