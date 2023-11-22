#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int num; cin >> num;
    if(num <= 6 || num == 9) {
        cout << "NO\n";
        return;
    } else {
        cout << "YES\n";
        if(num % 3 == 0) {
            cout << "1 4 " << num - 5 << "\n";
        } else {
            cout << "1 2 " << num - 3 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}