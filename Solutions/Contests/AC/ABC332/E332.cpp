#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ld total_weight;
ld target_weight;
int n, d; 

ld dfs(int item, int bag, ld curr_bag, ld score, vector<int> &v) {
    if(bag == d) {
        if(n == item) {
            return score;
        } else {
            return LDBL_MAX;
        }
    }
    if(item == n) {
        return dfs(item, bag + 1, 0, score + (target_weight - curr_bag) * (target_weight - curr_bag), v);
    }
    // cout << "item : " << item << " bag : " << bag << " curr_bag : " << curr_bag << " score : " << score << '\n';
    return min(
        dfs(item + 1, bag, curr_bag + v[item], score, v),
        dfs(item, bag + 1, 0, score + (target_weight - curr_bag) * (target_weight - curr_bag), v)
    );
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> d;
    vector<int> v(n);

    for(auto &x : v) cin >> x;

    total_weight = reduce(v.begin(), v.end());
    target_weight = total_weight / (ld)d;

    ld best = LDBL_MAX;

    std::default_random_engine e(std::chrono::system_clock::now().time_since_epoch().count());

    for(int i = 0; i < 10000; i++) {
        shuffle(v.begin(), v.end(), e);
        best = min(best, dfs(0,0,0,0,v));
    }

    cout << fixed << setprecision(10) << best / d << '\n';;

    return 0;
}