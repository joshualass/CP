#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> in(n);
    vector<int> a(n-1);

    for(int i = 0; i < n - 1; i++) {
        cin >> a[i];
        a[i]--;
        in[a[i]]++;
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i = 0; i < n; i++) {
        if(in[i] == 0) {
            pq.push({i,i});
        }
    }

    cout << a[0] + 1 << '\n';
    for(int i = n - 2; i >= 0; i--) {
        pair<int,int> p = pq.top();
        pq.pop();
        cout << a[i] + 1 << " " << p.second + 1 << '\n';

        in[a[i]]--;
        if(in[a[i]] == 0) {
            pq.push({max(a[i], p.first), a[i]});
        }

    }

    return 0;
}