#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll num; cin >> num;
    ll curr = 0;
    ll add = 1;
    ll cnt = 0;
    while(curr <= num) {
        curr += add;
        add *= 2;
        cnt++;
    }
    cout << cnt << '\n';
    return 0;
}