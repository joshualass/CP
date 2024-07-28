#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MOD = 998244353;

void remove(map<int,int> &m, multiset<int> &ms, int r) {
    m[r]--;
    if(m[r] == 0) {
        auto up = m.upper_bound(r);
        auto rit = m.find(r);
        if(up != m.end()) {
            ms.extract((*up).first - r);
        }
        if(rit != m.begin()) {
            ms.extract(r - (*prev(rit)).first);
        }
        if(rit != m.begin() && up != m.end()) {
            ms.insert((*up).first - (*prev(rit)).first);
        }
        m.erase(r);
    }
}

void add(map<int,int> &m, multiset<int> &ms, int a) {
    m[a]++;
    if(m[a] == 1) {
        map<int,int>::iterator up = m.upper_bound(a);
        map<int,int>::iterator ait = m.find(a);
        if(up != m.end() && ait != m.begin()) {
            ms.extract((*up).first - (*prev(ait)).first);
        }
        if(up != m.end()) {
            ms.insert((*up).first - a);
        }
        if(ait != m.begin()) {
            ms.insert(a - (*prev(ait)).first);
        }
    }
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    map<int,int> m;
    multiset<int> ms;
    multiset<int> nums;
    
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        add(m, ms, a[i]);
        nums.insert(a[i]);
    }
    ms.insert(0);
    int q; cin >> q;
    
    for(int i = 0; i < q; i++) {
        int idx, x; cin >> idx >> x;
        idx--;
        
        remove(m, ms, a[idx]);
        nums.erase(nums.find(a[idx]));
        
        add(m, ms, x);
        nums.insert(x);
        a[idx] = x;
        cout << (*--ms.end() + (*--nums.end())) << " \n"[i == q - 1];
    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}