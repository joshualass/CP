#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> in;
priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> out;
array<ll,2> a[200000];
ll res = 0;

void add(ll i) {
    res += a[i][0] * a[i][1];
    a[i][1] += 2;
    in.push({a[i][0] * a[i][1],i});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = 1;
        out.push({a[i][0] * a[i][1], i});
    }
    in.push(out.top());
    out.pop();
    while(out.size()) {
        array<ll,2> inbest = in.top(); in.pop(); add(inbest[1]);
        array<ll,2> outbest = out.top(); out.pop(); add(outbest[1]);
        // cout << "edge inside " << inbest[1] << " outside : " << outbest[1] << '\n';
    }
    
    cout << res << '\n';

    return 0;
}