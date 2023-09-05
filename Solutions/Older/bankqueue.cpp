#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, T; cin >> n >> T;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        int c, t; cin >> c >> t;
        v[i] = {t,c}; // time cost
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    ll money = 0;
    map<int,int> m; //money quantity
    int index = 0;
    for(int i = T - 1; i >= 0; i--) {
        while(index < n && v[index].first >= i) {
            int push = v[index].second;
            index++;
            // cout << "i: " << i << " inserting: " << push << " " << 1 << '\n';
            if(m.find(push) == m.end()) {
                m.insert({push,1});
            } else {
                m[push]++;
            }
        }
        if(m.size()) {
            pair<int,int> p = *(--m.end());
            // cout << "i: " << i << "f: " << p.first << " s: " << p.second << "\n";
            money += p.first;
            m[p.first]--;
            if((*(--m.end())).second == 0) {
                m.erase(p.first);
            }
        }
    }
    cout << money << "\n";

    return 0;
}