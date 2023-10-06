#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> v1(n);
    vector<int> v2(n);
    for(auto &x: v1) cin >> x;
    for(auto &x: v2) cin >> x;
    int l = 0, r = 1e9;
    while(l < r) {
        int m = (l + r) / 2;
        bool poss = true;
        stack<int> s;
        for(int i = 0; i < n; i++) {
            if(v1[i] > m) {
                if(s.size()) {
                    if(s.top() == v1[i]) {
                        s.pop();
                    } else {
                        poss = false;
                    }
                } else {
                    s.push(v1[i]);
                }
            }
        }
        if(s.size()) poss = false;
        stack<int> S;
        for(int i = 0; i < n; i++) {
            if(v2[i] > m) {
                if(s.size()) {
                    if(s.top() == v2[i]) {
                        s.pop();
                    } else {
                        poss = false;
                    }
                } else {
                    s.push(v2[i]);
                }
            }
        }
        if(S.size()) poss = false;
        if(poss) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << endl;
    return 0;
}