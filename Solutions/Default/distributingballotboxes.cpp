#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, b;
    cin >> n >> b;
    while(n != -1 && b != -1) {
        priority_queue<pair<int,pair<int,int>>> pq;
        for(int i = 0; i < n; i++) {
            int num; cin >> num;
            pq.push({ num, {num, 1}});
            b--;
        }
        while(b-->0) {
            pair<int, pair<int,int>> p = pq.top();
            pq.pop();
            pq.push({p.second.first / p.second.second + (p.second.first % p.second.second == 0 ? 0 : 1) , {p.second.first, p.second.second}});
        }
        int m = 0;
        while(pq.size()) {
            int m = max(m,pq.top().first);
            pq.pop();
        }
        cout << m << '\n';
        cin >> n >> b;
    }

    return 0;
}