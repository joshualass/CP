#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int update_scores(vector<ld> &v, vector<bool> &filled, vector<ld> &scores) {
    ld best = -1;
    int best_idx = 0;
    ld currscore = 0;
    int skippy = 0;
    for(int i = v.size() - 1; i >= 0; i--) {
        currscore += v[i] * (filled[i] ^ 1);
        if(filled[i]) skippy++;
        if(!filled[i]) {
            scores[i] = currscore / (v.size() - i - skippy);
        }

        if(!filled[i] && scores[i] > best) {
            best_idx = i;
            best = scores[i];
        }
    }
    return best_idx;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    ld n, m, s; cin >> n >> m >> s;
    vector<ld> v(n);
    vector<bool> filled(n);
    vector<ld> scores(n);
    ld score = 0;
    for(auto &x: v) cin >> x;

    while(s > 0) {
        int best_idx = update_scores(v,filled,scores);
        int empty_after = 0;
        for(int i = best_idx; i < n; i++) {
            if(!filled[i]) empty_after++;
        }
        // cout << "remaining : " << s << " best_idx : " << best_idx;
        if(s >= m * empty_after) { //fill all
            ld cap = m;
            // cout << " cap : " << cap << '\n';
            for(int i = best_idx; i < n; i++) {
                score += cap * v[i] * (filled[i] ^ 1);
                filled[i] = 1;
            }
            s -= m * empty_after;
        } else {
            ld cap = s / empty_after;
            // cout << " cap : " << cap << '\n';
            for(int i = best_idx; i < n; i++) {
                score += cap * v[i] * (filled[i] ^ 1);
            }
            break;
        }
        // break;
    }
    cout << score << '\n';
    return 0;
}