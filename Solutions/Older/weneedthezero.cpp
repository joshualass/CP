#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        int num = 0;
        for(int i = 0; i < n; i++) {
            int nn; cin >> nn;
            num ^= nn;
        }
        if(n % 2 == 0) {
            cout << (num == 0 ? "0" : "-1") << "\n";
        } else {
            cout << num << "\n";
        }
    }

    return 0;
}