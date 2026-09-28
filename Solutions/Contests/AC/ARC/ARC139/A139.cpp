#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll lo = 0;
    ll prevctz = 69;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        if(num < prevctz) {
            lo += (1LL << num);
        } else {
            //clear all bits set before num
            lo = (lo >> num) << num;
            if(lo >> num & 1LL) {
                lo += (2LL << num);
            } else {
                lo += (1LL << num);
            }
        }
        prevctz = num;
    }
    cout << lo << "\n";
    return 0;
}