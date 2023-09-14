#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t-->0) {
        int n, k;
        cin >> n >> k;
        int count = 1;
        for(int i = 0; i < n; i++) {
            int in;
            cin >> n;
            if(count == in) {
                count ++;
            }
        }
        int changes = n - count;
        int operations = changes / k;
        if(changes % k != 0) {
            operations ++;
        }
        cout << operations << "\n";
    }
    return 0;
}