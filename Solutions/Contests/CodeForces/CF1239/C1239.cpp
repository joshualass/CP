#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, p; cin >> n >> p;
    vector<int> seated(n);//0 - in seat, 1 - inq, 2 - porridge started
    vector<ll> res(n);
    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> events; //{time, 0 - person ready 1 - porridge done, id}

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        events.push({num,0,i});
    }

    queue<ll> q; //queue for porridge
    priority_queue<ll, vector<ll>, greater<ll>> inq; //used to find the minimum person still in the queue
    priority_queue<ll, vector<ll>, greater<ll>> rq; //used to find the next person to join the queue from all the ready people

    while(events.size()) {
        array<ll,3> a = events.top();
        events.pop();
        // cout << "a : " << a[0] << " " << a[1] << " " << a[2] << '\n';
        if(a[1] == 0) {
            rq.push(a[2]);
        } else {
            q.pop();
            res[a[2]] = a[0];
            seated[a[2]] = 0;
            while(inq.size() && seated[inq.top()] == 0) inq.pop();
        }
        //try to put ready person into q
        if(rq.size() && (inq.empty() || inq.size() && rq.top() < inq.top())) {
            ll id = rq.top();
            rq.pop();
            inq.push(id);
            q.push(id);
            seated[id] = 1;
        }
        //start next person porridge
        if(q.size() && seated[q.front()] == 1) {
            seated[q.front()] = 2;
            events.push({a[0] + p, 1, q.front()});
        }
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }

    return 0;
}