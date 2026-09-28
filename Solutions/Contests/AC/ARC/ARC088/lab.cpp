#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int odd_cnt = 0;
    for(int i = 0; i < n; i++) {
        odd_cnt += adj[i].size() & 1;
    }

    int a = odd_cnt / 2;

    auto poss = [&](int mp) -> bool {
        bool ok = 1;
        auto dfs = [&](auto &&self, int i, int p) -> int {
            vector<int> child_paths;
            for(int c : adj[i]) {
                if(c != p) {
                    child_paths.push_back(self(self, c, i));
                    if(!ok) return 0;
                }
            }

            sort(child_paths.begin(), child_paths.end());
            if(child_paths.size() % 2 == 0) {
                int can_match = 1;
                for(int i = 0; i < child_paths.size() / 2; i++) {
                    if(child_paths[i] + child_paths[child_paths.size() - 1 - i] > mp) {
                        can_match = 0;
                        break;
                    }
                }
                if(can_match) return 1;
                if(child_paths.back() > mp) {
                    ok = 0;
                    return 0;
                }
                child_paths.pop_back();
            }

            int bad = 0;
            for(int i = 1; i <= child_paths.size() / 2; i++) {
                if(child_paths[i] + child_paths[child_paths.size() - i] > mp) bad++;
            }

            for(int j = 0; j < child_paths.size(); j++) {
                if(bad == 0) {
                    if(child_paths[j] == mp && i) {
                        ok = 0;
                        return 0;
                    }
                    return child_paths[j] + 1;
                }
                if(j < child_paths.size() / 2) {
                    bad -= child_paths[j+1] + child_paths[child_paths.size() - 1 - j] > mp;
                    bad += child_paths[j] + child_paths[child_paths.size() - 1 - j] > mp;
                } else {
                    if(j != child_paths.size() - 1) {
                        bad -= child_paths[child_paths.size()-(j+2)] + child_paths[j+1] > mp;
                        bad += child_paths[child_paths.size()-(j+2)] + child_paths[j] > mp;
                    }
                }
            }

            ok = 0;
            return 0;
        };
        auto res = dfs(dfs, 0, -1);
        if(adj[0].size() % 2 == 0) {
            ok &= res == 1;
        } else {
            ok &= res - 1 <= mp;
        }
        return ok;
    };
    
    int l = 1, r = n - 1;
    while(l != r) {
        int m = (l + r) / 2;
        if(poss(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << a << " " << l << '\n';

    return 0;
}