#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<array<int,2>> ops;

    auto add_swap = [&](int i, int j) -> void {
        assert(i < j);
        a[i]++, a[j]--;
        swap(a[i], a[j]);
        ops.push_back({i, j});
    }; 

    auto swap_two_early = [&](int i, int j) -> void {
        int k = n - 1;
        add_swap(j, k);
        add_swap(i, k);
        add_swap(j, k);
    };

    auto swap_two_later = [&](int j, int k) -> void {
        int i = 0;
        add_swap(i, j);
        add_swap(i, k);
        add_swap(i, j);
    };

    auto swap_two = [&](int i, int j) {
        if(i) {
            swap_two_later(i, j);
        } else if(j != n - 1) {
            swap_two_early(i, j);
        } else {
            int m = 1;
            swap_two_early(i, m);
            swap_two_later(m, j);
            swap_two_early(i, m);
        }
    };

    if(accumulate(a.begin(), a.end(), 0) != accumulate(b.begin(), b.end(), 0)) {
        cout << "No\n";
        return 0;
    }

    if(n == 2) {
        if(a != b) {
            add_swap(0, 1);
            if(a != b) {
                cout << "No\n";
                return 0;
            }
        }
    }

    vector<array<int,2>> need, give;
    for(int i = 0; i < n; i++) {
        int d = b[i] - a[i];
        if(d < 0) {
            give.push_back({i, -d});
        } else if(d > 0) {
            need.push_back({i, d});
        }
    }   

    while(need.size()) {
        int n = need.back()[0], g = give.back()[0];
        // cout << "n : " << n << " g : " << g << '\n';
        if(n > g) {
            swap_two(g, n);
            add_swap(g, n);
        } else {
            add_swap(n, g);
            swap_two(n, g);
        }

        need.back()[1]--;
        give.back()[1]--;

        if(need.back()[1] == 0) need.pop_back();
        if(give.back()[1] == 0) give.pop_back();
    }

    cout << "Yes\n";
    cout << ops.size() << '\n';
    for(auto op : ops) {
        cout << op[0] + 1 << " " << op[1] + 1 << '\n';
    }

    assert(ops.size() <= 31000);

    // cout << "done a\n";
    // for(int x : a) cout << x << " ";
    // cout << '\n';

    return 0;
}
