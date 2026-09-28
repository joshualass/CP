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

    bool loss = true;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(v[i] % n != 0) {
                loss = false;
            }
        } else {
            if(v[i] - v[i-1] != 1) {
                loss = false;
            }
        }
    }

    cout << (loss ? "Bob" : "Alice") << '\n';

    return 0;
}