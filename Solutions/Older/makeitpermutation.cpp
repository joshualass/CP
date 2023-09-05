#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t-->0) {
        int n, c, d; cin >> n >> c >> d;
        vector<ll> v(0);
        set<ll> s;
        ll cost = 0;
        for(int i = 0; i < n; i++) {
            ll num; cin >> num;
            if(s.find(num) != s.end()) {
                cost += c;
            } else {
                v.push_back(num);
                s.insert(num);
            }
        }
        sort(v.begin(),v.end());
        if(v[0] != 1) {
            v.insert(v.begin(),1);
            cost+= d;
        }
        
        ll cost2 = LLONG_MAX;
        for(ll i = 0; i < v.size(); i++) {
            cost2 = min(cost2, d*(v[i] - 1 - i) + c*(((ll)v.size())-(i+1)));
        }
        cout << cost + cost2 << "\n";
    }

    return 0;
}