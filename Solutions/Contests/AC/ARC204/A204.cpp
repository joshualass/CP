#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void simulate(int n, vector<int> a, vector<int> b) {
    vector<int> cnts(accumulate(b.begin(), b.end(), 1));
    deque<int> q;
    vector<int> avis(n);
    auto dfs = [&](auto self, int c) -> void {
        if(q.size()) {
            int x = q.front();
            q.pop_front();
            self(self, c + b[x]);
            q.push_front(x);
        } 
        if(count(avis.begin(), avis.end(), 0)) {
            for(int i = 0; i < n; i++) {
                if(avis[i] == 0) {
                    avis[i] = 1;
                    q.push_back(i);
                    self(self, max(0,c - a[i]));
                    q.pop_back();
                    avis[i] = 0;
                    break;
                }
            }
        }
        if(q.empty() && count(avis.begin(), avis.end(), 0) == 0) {
            cnts[c]++;
        }
    };

    dfs(dfs, 0);

    cout << "cnts : " << cnts << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r; cin >> n >> l >> r;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    simulate(n, a, b);

    

    return 0;
}
