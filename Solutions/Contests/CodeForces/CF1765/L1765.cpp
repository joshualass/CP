#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

map<string,int> days = {
    {"Monday", 0},
    {"Tuesday", 1},
    {"Wednesday", 2},
    {"Thursday", 3},
    {"Friday", 4},
    {"Saturday", 5},
    {"Sunday", 6}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        for(int j = 0; j < t; j++) {
            string s; cin >> s;
            assert(days.count(s));
            int bit = days[s];
            a[i] += 1 << bit;
        }
    }

    vector<int> h;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        h.push_back(x - 1);
    }

    vector<vector<int>> p(k);
    vector<int> ptr(k);
    int completed = 0, day = 0;

    vector<set<int>> pw(n); //for each employee i, stores which projects that are dependent on them
    vector<set<int>> ew(7); //for each day of the week i, stores which employees work this week and have a project to work on

    for(int i = 0; i < k; i++) {
        int t; cin >> t;
        for(int j = 0; j < t; j++) {
            int x; cin >> x;
            x--;
            p[i].push_back(x);
            if(j == 0) {
                pw[x].insert(i);
                for(int z = 0; z < 7; z++) {
                    if((a[x] >> z) & 1) {
                        ew[z].insert(x);
                    }
                }
            }
        }
    }

    int hp = 0;

    vector<int> res(k);

    while(completed < k) {

        // cout << "day : " << day + 1 << endl;

        if(hp < m && h[hp] == day) {
            day++;
            hp++;
            continue;
        }

        int wd = day % 7;
        vector<int> add, rem;
        vector<array<int,2>> nxzzz;
        for(int x : ew[wd]) {
            assert(!pw[x].empty());
            int project = *pw[x].begin();
            pw[x].erase(pw[x].begin());
            if(pw[x].empty()) {
                rem.push_back(x);
            }
            // cout << "employee x : " << x + 1 << " works on project : " << project + 1 << endl;
            ptr[project]++;
            if(ptr[project] == sz(p[project])) {
                res[project] = day + 1;
                completed++;
                // cout << "project " << project + 1 << " complete." << endl;
            } else {
                int nx = p[project][ptr[project]];
                // cout << "add nx : " << nx << " to queue" << endl;
                nxzzz.push_back({nx, project});
                // pw[nx].insert(project);
                // if(pw[nx].size() == 1) {
                //     add.push_back(nx);
                // }
            }
        }

        for(int x : rem) {
            for(int z = 0; z < 7; z++) {
                if((a[x] >> z) & 1) {
                    ew[z].erase(x);
                }
            }
        }
        
        for(auto [nx, project] : nxzzz) {
            pw[nx].insert(project);
            if(sz(pw[nx]) == 1) {
                for(int z = 0; z < 7; z++) {
                    if((a[nx] >> z) & 1) {
                        ew[z].insert(nx);
                    }
                }
            }
        }

        day++;
    }

    cout << res << '\n';

    // set<int> h;
    // for(int i = 0; i < m; i++) {
    //     int x; cin >> x;
    //     h.insert(x - 1);
    // }

    // vector<vector<int>> p(k);
    // int lp = 0;
    // for(int i = 0; i < k; i++) {
    //     int t; cin >> t;
    //     lp = max(lp, t);
    //     for(int j = 0; j < t; j++) {
    //         int x; cin >> x;
    //         p[i].push_back(x - 1);
    //     }
    // }

    // int mw = m + lp;
    // vector<vector<int>> nh(7);

    // for(int i = 0; i < 7; i++) {
    //     for(int j = 0; j < mw; j++) {
    //         if(h.count(j * 7 + i) == 0) {
    //             nh[i].push_back(j * 7 + i);
    //         }
    //     }
    // }

    // for(int i = 0; i < k; i++) {
    //     int cur = -1;
    //     for(int emp : p[i]) {
    //         int nx = INT_MAX;
    //         for(int j = 0; j < 7; j++) {
    //             if((a[emp] >> j) & 1) {
    //                 nx = min(nx, *upper_bound(nh[j].begin(), nh[j].end(), cur));
    //             }
    //         }
    //         cur = nx;
    //     }
    //     cout << cur + 1 << " \n"[i == k - 1];
    // }

    return 0;
}
