#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p, t; cin >> p >> t;

    vector<string> teams(t);

    for (auto& team : teams) {
        cin >> team;
    }

    int cnt = 0;

    set<int> bad_teams;

    for (int i =0 ; i < t; ++i) {
        set<char> team;
        for (auto c : teams[i]) {
            if (team.count(c)) {
                bad_teams.insert(i);
            }
            if (c - 'A' >= p) {
                bad_teams.insert(i);
            }
            team.insert(c);
        }
    }
    // cerr << "hello" << endl;

    auto check = [&](int k) -> bool {
        set<char> used;
        // cerr << "k : " << k << endl;
        // for (auto c : avail) {
        //     cerr << c << " ";
        // }
        // cerr << endl;
        for (int j = 0; j < t; ++j) {
            if (k & (1 << j)) {
                if (bad_teams.count(j))
                    return false;
                // cerr << "k : " << k << " j : " << j << endl;
                // insert team
                for (auto c : teams[j]) {
                    if (c - 'A' >= p) {
                        return false;
                    }
                    if (used.count(c))
                        return false;
                    used.insert(c);
                }
            }
        }

        return true;
        
    };

    // check(3);

    for (int i = 1; i < (1 << t); ++i) {
        if (__builtin_popcount(i) <= cnt)
            continue;
        if (check(i))
            cnt = max(cnt, __builtin_popcount(i));
    }

    cout << cnt << endl;

    return 0;
}