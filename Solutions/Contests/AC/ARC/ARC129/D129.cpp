#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);

    for(auto &x: v) cin >> x;

    //check not possible
    if(n & 1) {
        if(reduce(v.begin(),v.end()) != 0) {
            cout << "-1\n";
            return 0;
        }
    } else {
        int sum1 = 0, sum2 = 0;
        for(int i = 0; i * 2 < n; i++) {
            sum1 += v[i * 2];
            sum2 += v[i * 2 + 1];
        }
        if((sum1 & 1) || (sum2 & 1) || reduce(v.begin(),v.end()) != 0) {
            cout << "-1\n";
            return 0;
        }
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<ll> ops(n);

    for(int i = 0; i < n; i++) {
        if(v[i] < 0) {
            pq.push({v[i], i});
        }    
    }

    int cnts = 0;

    while(pq.size()) {
        cnts++;
        pair<int,int> p = pq.top();
        pq.pop();
        if(v[p.second] >= 0) continue;
        int left = (p.second - 1 + n) % n;
        int right = (p.second + 1) % n;
        int bag = (p.first * -1 + 1) / 2;
        v[p.second] += bag * 2;
        v[left] -= bag;
        v[right] -= bag;
        ops[p.second] += bag;
        if(v[left] < 0) {
            pq.push({v[left],left});
        }
        if(v[right] < 0) {
            pq.push({v[right],right});
        }
        if(cnts > 1e7) {
            cout << "-1\n";
            return 0;
        }
    }   

    ll ans = 0;
    ll least = LLONG_MAX;

    for(int i = 0; i < n; i++) {
        ans += ops[i];
        least = min(least, ops[i]);
    }

    cout << ans - least * n << '\n';

    return 0;
}