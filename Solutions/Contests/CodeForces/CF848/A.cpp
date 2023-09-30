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
        vector<int> v(n);
        int sum = 0;
        int best = 5;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            sum += v[i];
            if(i != 0) {
                best = min(v[i] + v[i-1],best);
            }
        }
        cout << (sum-best*2) << "\n";
    }

    return 0;
}