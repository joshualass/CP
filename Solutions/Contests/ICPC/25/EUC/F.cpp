#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<bool> vb;
using pi = pair<int, int>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for (auto& s : a)
        cin >> s;

    vi ids(n);

    string ly; cin >> ly;

    vvi tr(26);

    int bad_idx = 0;

    rep(i, 0, n) {
        tr[a[i][0] - 'a'].push_back(i);
    }

    auto cnt = [&]() -> int {
        int ct = 0;
        for (auto x : tr)
            ct += x.size();
        return ct;
    };

    string ans = "";

    // cerr << "hey" << endl;

    // cerr << "tr\n";
    // for (auto x : tr) {
    //     for (auto y : x)
    //         cerr << y << " ";
    //     cerr << endl;
    // }

    int cntt = 0;

    while (bad_idx < ly.size() && cnt() && cntt < 15) {
        // cntt++;
        bool found = false;
        // cerr << "ans : " << ans << endl;
        rep(i, 0, 26) {
            // cerr << "i : " << i << endl;
            if (i == (ly[bad_idx] - 'a'))
                continue;
            if (tr[i].size()) {
                // cerr << "FOUND. " << i << endl;
                // good
                ans += ('a' + i);
                found = true;
                vector<pi> to_push;
                for (auto idx : tr[i]){ 
                    // transition
                    ids[idx]++;
                    if (ids[idx] < a[idx].size()) {
                        int nex = (a[idx][ids[idx]]) - 'a';
                        // tr[nex].push_back(idx);
                        to_push.push_back({nex, idx});
                    } else {
                        // cerr << "HIIII. " << idx << endl;
                    }
                }
                tr[i].clear();
                for (auto p : to_push){ 
                    tr[p.first].push_back(p.second);
                }

                break;
            }
        }

        if (found)
            continue;
        
        // have to take from bad
        ans += ly[bad_idx];
        int bad_ch = ly[bad_idx++] - 'a';
        // cerr << "BAD_CH : " << bad_ch << endl;
        vector<pi> to_push;
        for (auto idx : tr[bad_ch]){ 
            // transition
            ids[idx]++;
            if (ids[idx] < a[idx].size()) {
                int nex = (a[idx][ids[idx]]) - 'a';
                to_push.push_back({nex, idx});
            }
        }
        tr[bad_ch].clear();
        for (auto p : to_push){ 
            tr[p.first].push_back(p.second);
        }
    }

    if (bad_idx < ly.size()) {
        cout << "YES\n";
        cout << ans << endl;
    } else
        cout << "NO\n";

    return 0;
}