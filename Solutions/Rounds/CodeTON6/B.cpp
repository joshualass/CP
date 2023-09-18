#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    int a = 0;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a ^= num;
    }
    if(n % 2) {
        int least = a;
        int most = a;
        for(int i = 0; i < m; i++) {
            int num; cin >> num;
            most |= num;
        }
        cout << least << " " << most << "\n";
    } else {
        int most = a;
        int least = a;
        for(int i = 0; i < m; i++) {
            int num; cin >> num;
            least -= least & num;
        }
        cout << least << " " << most << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}