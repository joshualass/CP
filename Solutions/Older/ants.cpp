#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc; cin >> tc;
    while(tc-->0) {
        int l, n; cin >> l >> n;
        int low = 0;
        int high = l;
        int most = 0;
        int least = 0;
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            if(num > l) {
                continue;
            }
            most = max(most, max(num - low, high -num));
            least = max(least, min(num - low, high - num));
        }
        cout << least << " " << most << '\n';

    }

    return 0;
}