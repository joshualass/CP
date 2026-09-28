#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;

    map<int,int> m;
    set<int> s;
    vector<int> v(n);

    for(int i = 0; i < 200001; i++) {
        s.insert(i);
        m[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        m[num]++;
        v[i] = num;
        if(num < 200000) {
            s.erase(num);
        }
    }

    for(int i = 0; i < q; i++) {
        int idx, x; cin >> idx >> x;
        idx--;
        if(v[idx] < 200000) {
            m[v[idx]]--;
            if(m[v[idx]] == 0) {
                s.insert(v[idx]);
            }
        }
        if(x < 200000) {
            if(m[x] == 0) {
                s.erase(x);
            }
            m[x]++;
        }
        v[idx] = x;
        cout << (*s.begin()) << '\n';
    }

    return 0;
}