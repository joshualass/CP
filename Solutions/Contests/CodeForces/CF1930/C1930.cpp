#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> ranges;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        ranges.push_back({num+i+1,num+1});
    }
    sort(ranges.rbegin(), ranges.rend());
    priority_queue<int> pq;
    int high = 2e9;
    for(int i = 0; i < n; i++) {
        //check if there's intersection
        if(ranges[i].first >= high - pq.size()) {
        } else {
            while(pq.size()) {
                cout << high << " ";
                pq.pop();
                high--;
            }
            high = ranges[i].first;
        }
        pq.push(ranges[i].second);
    }
    while(pq.size()) {
        cout << high << " ";
        pq.pop();
        high--;
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}