#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q; cin >> q;
    vector<ll> lengths(1,9);
    int length = 2;
    ll val = 90;
    while(true) {
        lengths.push_back(val*length);
        length++;
        if(val > LLONG_MAX/10) {
            break;
        }
        val *= 10;
        
    }
    while(q-->0) {
        ll num; cin >> num;
        num--;
        int idx = 0;
        while(num - lengths[idx] > 0) {
            num -= lengths[idx++];
        }
 
        ll value = 1;
        for(int i = 0; i < idx; i++) {
            value *= 10;
        }
        value += num / (idx + 1);
        int digit = idx - num % (idx + 1);
        // cout << "num: " << num << " idx: " << idx << " value: " << value << " digit: " << digit << "\n";
        while(digit-- > 0) {
            value /= 10;
        }
        cout << value % 10 << "\n";
    }
 
    return 0;
}
