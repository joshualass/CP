#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &x: v) cin >> x;

    vector<pair<int,int>> order(n);
    for(int i = 0; i < n; i++) {    
        order[i] = {v[i],i};
    }
    sort(order.begin(), order.end(), [] (const pair<int,int> &lhs, const pair<int,int> &rhs) -> bool {
        if(lhs.first == rhs.first) {
            return lhs.second < rhs.second;
        } else {
            return lhs.first > rhs.first;
        }
    });

    int best = 1e9;
    int curr_leftmost = 1e9;
    for(int i = 0; i < n; i++) {
        if(order[i].second < k) {
            if(curr_leftmost != 1e9) {
                best = min(best, curr_leftmost - order[i].second);
            }
        } else {
            curr_leftmost = min(curr_leftmost, order[i].second);
        }
    }
    if(best == 1e9) {
        cout << "-1\n";
    } else {
        cout << best << "\n";
    }
    return 0;
}