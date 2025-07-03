#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    set<int> s(a.begin(), a.end());
    map<int,int> m;
    int i = 0;
    for(int x : s) {
        m[x] = i++;
    }
    for(int &x : a) x = m[x];
    int c = s.size();

    // cout << "a : " << a << " c : " << c << '\n';
    //no thanks

    auto work = [&](int r) -> pair<int,vector<vector<int>>> {
        vector<deque<int>> ac(c);
        vector<int> ranges(n,-1);
        for(int i = 0; i < n; i++) {
            if(ac[a[i]].size() == r) {
                ranges[ac[a[i]][0]] = i;
                ac[a[i]].pop_front();
            }
            ac[a[i]].push_back(i);
        }
        for(int i = 0; i < c; i++) {
            for(int x : ac[i]) ranges[x] = n;
        }
        vector<deque<int>> stops(c);
        multimap<int,int> mm;
        priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> pq; //{r, clr}
        for(int i = 0; i < r; i++) {
            mm.insert({-1,i});
            pq.push({n * 2, -1});    
        }

        cout << "r : " << r << " ranges : " << ranges << '\n';

        vector<vector<int>> res(r);
        for(int i = 0; i < n; i++) {
            if(stops[a[i]].empty()) {
                pq.push({ranges[i], a[i]});
            }
            stops[a[i]].push_back(ranges[i]);
            assert(pq.size());
            if(pq.top()[0] <= i) return pair<int,vector<vector<int>>>{0,vector<vector<int>>{}}; //if we missed an r
            auto [r, clr] = pq.top();
            pq.pop();
            if(pq.top()[1] != a[i]) { //if this color is not same as highest priority
                int row = mm.find(clr)->second;
                res[row].push_back(i);
                mm.erase(mm.find(clr));
                mm.insert({a[i],row});
                if(clr != -1) stops[clr].pop_front();
                if(stops[clr].size()) {
                    pq.push({stops[clr][0],clr});
                } else {
                    pq.push({n,clr});
                }
            } else {
                if(pq.empty()) return pair<int,vector<vector<int>>>{0,vector<vector<int>>{}}; //no home
                if(pq.top()[0] <= i) return pair<int,vector<vector<int>>>{0,vector<vector<int>>{}}; //if we missed an r
                auto [r2,clr2] = pq.top();
                pq.pop();
                int row = mm.find(clr2)->second;
                res[row].push_back(i);
                mm.erase(mm.find(clr2));
                mm.insert({a[i],row});
                if(clr2 != -1) stops[clr2].pop_front();
                if(stops[clr2].size()) {
                    pq.push({stops[clr2][0], clr2});
                } else {
                    pq.push({n,clr2});
                }
                pq.push({r,clr});
            }
        }
        return {1,res};
    };

    int l = 1, r = n;
    while(l != r) {
        int m = (l + r) / 2;
        if(work(m).first) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    vector<vector<int>> res = work(l).second;
    cout << res.size() << '\n';
    for(auto row : res) {
        cout << row.size() << " ";
        for(int i = 0; i < row.size(); i++) {
            cout << row[i] << " \n"[i == row.size() - 1];
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}