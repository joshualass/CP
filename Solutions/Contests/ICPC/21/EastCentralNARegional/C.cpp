#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

vector<int> p0 = {0, 5, 1, 2, 3, 4, 10, 6, 7, 8, 9, 19, 20, 11, 12, 13, 14, 15, 16, 17, 18, 25, 21, 22, 23, 24, 30, 26, 27, 28, 29};
vector<int> p1 = {0, 8, 3, 7, 13, 14, 4, 2, 12, 22, 15, 5, 1, 6, 11, 21, 27, 28, 23, 16, 9, 10, 20, 26, 29, 17, 18, 19, 25, 30, 24};

vector<bool> rot(vector<bool>& a, vector<int>& p){
    vector<bool> b(31, true);
    for(int i = 0; i < p.size(); i++){
        b[i] = a[p[i]];
    }
    return b;
}

set<vector<bool>> calc_v(vector<bool>& a) {
    queue<vector<bool>> q;
    set<vector<bool>> s;
    s.insert(a);
    q.push(a);
    while(q.size() != 0){
        vector<bool> cur = q.front();
        q.pop();
        vector<bool> n0 = rot(cur, p0);
        vector<bool> n1 = rot(cur, p1);
        if(!s.count(n0)) {
            s.insert(n0);
            q.push(n0);
        }
        if(!s.count(n1)) {
            s.insert(n1);
            q.push(n1);
        }
    }
    return s;
}

bool is_valid(vector<bool> a, vector<bool> b, vector<bool> c){
    for(int i = 0; i < a.size(); i++){
        if(!(a[i] || b[i] || c[i])) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<bool>> a(3, vector<bool>(31, false));
    int nsum = 0;
    for(int i = 0; i < 3; i++){
        int n;
        cin >> n;
        nsum += n;
        a[i][0] = true;
        for(int j = 0; j < n; j++){
            int tmp;
            cin >> tmp;
            a[i][tmp] = true;
        }
    }
    if(nsum != 30){
        cout << "No\n";
        return 0;
    }
    set<vector<bool>> s0, s1;
    s0 = calc_v(a[0]);
    s1 = calc_v(a[1]);
    for(auto i = s0.begin(); i != s0.end(); i++){
        for(auto j = s1.begin(); j != s1.end(); j++){
            if(is_valid(*i, *j, a[2])) {
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";

    return 0;
}