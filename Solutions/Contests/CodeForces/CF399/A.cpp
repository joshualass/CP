#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    int curr = 1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == curr) curr++;
        curr++;
    }
    cout << --curr << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}