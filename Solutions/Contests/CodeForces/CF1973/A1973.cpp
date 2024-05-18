#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int a, b, c; cin >> a >> b >> c;
    if((a + b + c) & 1) {
        cout << "-1\n";
        return;
    }
    int res = 0;
    priority_queue<int> pq;
    pq.push(a);
    pq.push(b);
    pq.push(c);

    while(pq.size()) {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        if(x && y) {
            x--;
            y--;
            res++;
            pq.push(x);
            pq.push(y);
        } else {
            break;
        }
    }

    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}