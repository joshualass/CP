#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    string str; cin >> str;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(str[i] == 'B') {
            cnt++;
            i += k-1;
        }
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}