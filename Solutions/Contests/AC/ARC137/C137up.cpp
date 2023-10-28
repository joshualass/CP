#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);

    for(auto &x: v) cin >> x;

    if(v[n-1] - v[n-2] > 1) {
        cout << "Alice\n";
    } else if((v[n-1] - n) & 1) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }

    return 0;
}