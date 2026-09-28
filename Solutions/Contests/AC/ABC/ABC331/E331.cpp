#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, l; cin >> n >> m >> l;
    // vector<int> a(n);
    // vector<int> b(m);

    // for(auto &x : a) cin >> x;

    // for(auto &x : b) cin >> x;

    vector<pair<int,int>> a(n);
    vector<pair<int,int>> b(m);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        a[i] = {num, i};
    }

    for(int i = 0; i < m; i++) {
        int num; cin >> num;
        b[i] = {num, i};
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    set<pair<int,int>> s;

    for(int i = 0; i < l; i++) {
        int c, d; cin >> c >> d;
        c--; d--;
        s.insert({c,d});
    }
    

    priority_queue<array<int,3>> pq;

    for(int i = 0; i < n; i++) {
        pq.push({a[i].first + b[m-1].first, i, m - 1});
        // cout << "push ? " << (a[i].first + b[m-1].first) << '\n';
    }

    int ans = -1;

    while(true) {
        array<int,3> arr = pq.top();
        pq.pop();
        if(s.find({a[arr[1]].second,b[arr[2]].second}) == s.end()) {
            // cout << "a : " << arr[1] << " b : " << arr[2] << '\n';
            ans = arr[0];
            break;
        }
        if(arr[2] != 0) {
            pq.push({a[arr[1]].first + b[arr[2]-1].first, arr[1], arr[2]-1});
        }
    }

    cout << ans << '\n';

    return 0;
}