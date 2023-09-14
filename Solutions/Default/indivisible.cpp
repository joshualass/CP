#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        if(n == 1) {
            cout << "1\n";
            continue;
        }
        if(n % 2 == 1) {
            cout << "-1\n";
            continue;
        }
        for(int i = 1; i <= n; i++) {
            if(i%2) {
                cout << i + 1 << " ";
            } else {
                cout << i - 1 << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}