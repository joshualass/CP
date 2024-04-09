#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, d; cin >> n >> d;
    vector<pair<int,int>> a(n);
    for(auto &p : a) {
        cin >> p.first >> p.second; 
        p.first *= -1;
        p.second++;
    }
    
    queue<array<int,3>> q;  //original queue
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq; //people that reenter the queue
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> toe; //people that are eating and and we enter pq
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> mpq; //highest priority person in queue 

    for(int i = 0; i < n; i++) {
        q.push({a[i].first, -1, i});
        mpq.push({a[i].first, -1, i});
    }

    int cnt = 0;
    int i = 1;
    vector<bool> fed(n);

    for(; i <= d; i++) {

        while(mpq.size() && fed[mpq.top()[2]]) mpq.pop();

        while(toe.size() && toe.top()[0] == i) {
            array<int,3> arr = toe.top();
            toe.pop();
            pq.push({a[arr[2]].first, cnt++, arr[2]});
        }

        array<int,3> f;
        if(pq.size() && (pq.top() < mpq.top())) {
            f = pq.top();
            pq.pop();
        } else {
            f = q.front();
            q.pop();
        }

        fed[f[2]] = 1;

        toe.push({i + a[f[2]].second, a[f[2]].second, f[2]});
 
        if(q.empty()) break;
    }
 
    cout << (q.empty() ? i : -1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}