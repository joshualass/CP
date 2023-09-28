//https://codeforces.com/contest/977/problem/F
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    map<int,vector<int>> m; //index, maximum length at index
    int best = -1;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        if(m.find(num-1) == m.end()) {
            if(m.find(num) == m.end()) {
                m[num] = {i};
                if(best == -1 || m[best].size() < m[num].size()) {
                    best = num;
                }
            } //if previous doesn't exist and current exist, it will never be better
        } else {
            if(m.find(num) == m.end() || m.find(num) != m.end() && m[num-1].size() + 1 > m[num].size()) {
                m[num] = move(m[num-1]);
                m[num].push_back(i);
                m.erase(num-1);
                if(best == -1 || m[best].size() < m[num].size()) {
                    best = num;
                }
            }
        }
    }
    vector<int> v = m[best];
    cout << v.size() << "\n";
    for(auto &x : v) cout << ++x << " ";
    cout << endl;

    return 0;
}