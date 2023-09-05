#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, B; cin >> N >> B;
    while(N != -1 && B != -1) {
        priority_queue<pair<int, pair<int,int>>> pq;
        B -= N;
        for(int n = 0; n < N; n++) {
            int num ;cin >> num;
            pq.push({num, {num, 1}});
        }
        while(B-->0) {
            pair<int, pair<int,int>> p = pq.top();
            pq.pop();
            pq.push({p.second.first / (p.second.second + 1) + (p.second.first % (p.second.second + 1) == 0 ? 0 : 1), {p.second.first, p.second.second + 1}});
        }
        int m = 0;
        while(pq.size()) {
            pair<int, pair<int,int>> p = pq.top();
            pq.pop();
            m = max(m, p.first);
        }
        cout << m << '\n';
        cin >> N >> B;
    }

    return 0;
}