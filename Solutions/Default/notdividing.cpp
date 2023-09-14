#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t; cin >> t;
    while(t-->0) {
        int n; cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            if(num == 1) {
                num++;
            }
            v[i] = num;
        }
        for(int i = 1; i < n; i++) {

            while(v[i] % v[i-1] == 0) {
                v[i]++;
            }
        }
        for(int x : v) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}