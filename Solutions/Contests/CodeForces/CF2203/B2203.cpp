#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll x; cin >> x;
    int sum = 0;
    priority_queue<int> pq;
    while(x) {
        sum += x % 10;
        if(x < 10) {
            pq.push(x % 10 - 1);
        } else {
            pq.push(x % 10);
        }
        x /= 10;
    }

    int ops = 0;
    while(sum > 9) {
        ops++;
        sum -= pq.top();
        pq.pop();
    }

    cout << ops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}