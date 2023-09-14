#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int S;
    cin >> S;
    vector<ll> v(S+1);
    if(S < 3) {
        cout << 0;
    } else {
        v[3] = 1;
        v[4] = 1;
        v[5] = 1;
        for(int i = 6; i < v.size(); i++) {
            ll num = (v[i-1] + v[i-3]) % 1000000007;
            v[i] = num;
        }
        cout << v[S];
    }

    return 0;
}