#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> v = {1,2,3,4,1,2,3,5,6,3,3,4,4,3,2,2,4,3,6,7,8,5,5};

    cout << count(v.begin(), v.end(), 3) << '\n';    

    int i = 8;
    while(i--) {
        cout << "i : " << i << '\n';
    }

    return 0;
}