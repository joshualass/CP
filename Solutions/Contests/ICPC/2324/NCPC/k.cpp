#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //look for element that is bigger than n
    ll p_x = 1;
    ll x = 2;
    while(true) {
        cout << "buf[" << x << "]" << endl;
        int val;
        cin >> val;
        if(val == 0){
            break;
        }
        p_x = x;
        x *= 2;
    }
    ll low = p_x + 1;
    ll high = x - 1;
    ll ans = x;
    while(low <= high) {
        ll mid = low + (high - low) / 2;
        cout << "buf[" << mid << "]" << endl;
        int val;
        cin >> val;
        if(val == 0){
            high = mid - 1;
            ans = min(ans, mid);
        }
        else {
            low = mid + 1;
        }
    }
    cout << "strlen(buf) = " << ans << endl;


    return 0;
}