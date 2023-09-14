#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        if(n % 2 == 0) {
            cout << 1 << " " << n/2 << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}