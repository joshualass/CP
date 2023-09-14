#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a + b == c) {
            cout << "+\n";
        } else {
            cout << "-\n";
        }
    }

    return 0;
}