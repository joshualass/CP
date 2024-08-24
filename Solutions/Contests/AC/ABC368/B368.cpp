#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int ops = 0;


    while(a.size() >= 2) {

        sort(a.rbegin(), a.rend());

        ops++;

        a[0]--;
        a[1]--;
        if(a[1] == 0) {
            a.erase(a.begin() + 1, a.begin() + 2);
        }
        if(a[0] == 0) {
            a.erase(a.begin(), a.begin() + 1);
        }

    }
    

    cout << ops << '\n';

    return 0;
}