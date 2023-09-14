#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) {
        int n; cin >> n;
        vector<int> v(n);
        int sum = 0;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            sum+= v[i];
        }
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(sum/n >= v[i]) {
                cnt++;
            }
        }
        cout << setprecision(3) << fixed << (1-(ld)cnt/(ld)n) * 100 << "%\n";
    }

    return 0;
}