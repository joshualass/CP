#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k; cin >> n >> m >> k;

    vector<set<int>> specials(n);

    for(int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        r--; c--;
        specials[r].insert(c);
    }
    

    set<int> lvisited;

    for(int i = 0; i < m; i++) {
        lvisited.insert(i);
    }
    set<pair<int,int>> ladds;
    specials[n-1].insert(m-1);
    ladds.insert({n-1,m-1});
    for(int row = n - 1; row >= 0; row--) {
        for(int i : specials[row]) {
            lvisited.erase(i);
        }
        if(lvisited.size()) {
            int nextl = (*--lvisited.end());
            if(specials[row].size() && nextl > (*--specials[row].end()) || specials[row].size() == 0) {
                lvisited.insert(nextl);
                ladds.insert({row,nextl});
                lvisited.erase(nextl);
                // cout << "adding : " << make_pair(row,nextl) << '\n';
            }   
        }
    }

    cout << (ladds.count({0,0}) ? "Bhinneka" : "Chaneka") << '\n';

    return 0;
}