#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(num == i + 1) {
            cnt++;
        }
    }
    cout << (cnt+1) /2 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
