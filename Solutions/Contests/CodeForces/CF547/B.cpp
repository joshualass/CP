#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> maxes(n);

    stack<pair<int,int>> s;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        int insertidx = i;
        while(s.size() && s.top().first >= num) {
            insertidx = s.top().second;
            maxes[i - s.top().second - 1] = max(maxes[i - s.top().second - 1], s.top().first);
            s.pop();
        }
        s.push({num,insertidx});
        maxes[i - s.top().second] = max(maxes[i - s.top().second], s.top().first);
    }
    while(s.size()) {
        maxes[n - 1 - s.top().second] = max(maxes[n - 1 - s.top().second], s.top().first);
        s.pop();
    }
    for(int i = n - 2; i >= 0; i--) {
        maxes[i] = max(maxes[i], maxes[i+1]);
    }
    for(int i = 0; i < n; i++) {
        cout << maxes[i] << " \n"[i == n - 1];
    }

    return 0;
}