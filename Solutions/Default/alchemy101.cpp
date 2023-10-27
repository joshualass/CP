// https://open.kattis.com/problems/alchemy101
/*
i tried solving this in highschool and had a stroke. it's not difficult. at all.
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    int curr = 0;
    for(int i = 1; i <= n; i++) {
        curr ^= i;
    }
    if(curr == n) {
        cout << n << "\n";
    } else {
        cout << n - 1 << "\n";
    }
    int skip = n ^ curr;
    for(int i = 1; i <= n; i++) {
        if(i != skip) {
            cout << i << " ";
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}