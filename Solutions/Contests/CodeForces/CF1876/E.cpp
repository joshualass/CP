#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//functional graph problem. idea is to turn the problem into a graph problem and use topological sort

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v(n);
    vector<int> indegrees(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        indegrees[num]++;
        v[i] = num;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }
    vector<int> states(n,-1); //-1 - unassigned, 0 - uncircled, 1 - circled

    //work on dag part
    while(q.size()) {
        int i = q.front();
        q.pop();
        states[i] = 0;
        if(states[v[i]] == -1) {
            states[v[i]] = 1;
            indegrees[v[v[i]]]--;
            if(indegrees[v[v[i]]] == 0) {
                q.push(v[v[i]]);
            }
        }
    }

    //only cycles left
    bool ok = 1;
    for(int i = 0; i < n; i++) {
        if(states[i] == -1) {
            q.push(i);
            while(q.size()) {
                int j = q.front();
                q.pop();
                states[j] = 0;
                if(states[v[j]] == 0) {
                    ok = 0;
                    break;
                }
                states[v[j]] = 1;
                if(states[v[v[j]]] == -1) {
                    q.push(v[v[j]]);
                }
            }
        }
    }

    if(ok) {
        cout << count(states.begin(), states.end(),0) << '\n';
        for(int i = 0; i < n; i++) {
            if(states[i] == 0) {
                cout << v[i] + 1 << ' ';
            }
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}