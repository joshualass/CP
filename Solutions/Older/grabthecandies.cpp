#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {

        int n; cin >> n;
        int even = 0;
        int odd = 0;
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            if(num % 2 == 0) {
                even+= num;
            } else {
                odd += num;
            }
        }
        if(even > odd) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}