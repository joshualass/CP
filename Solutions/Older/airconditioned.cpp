#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    while(n-->0) {
        int l, r;
        cin >> l >> r;
        pq.push({r,l}); //r first 
    }

    int lowest = 0;
    int placed = 0;
    while(pq.size()) {
        lowest = pq.top().first;
        pq.pop();
        placed++;
        while(pq.size() && pq.top().second <= lowest) {
            pq.pop();
        }
    }
    cout << placed << '\n';
    return 0;
}