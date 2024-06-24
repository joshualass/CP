#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &p : a) {
        cin >> p.first >> p.second;
    }

    vector<int> res(31);
    for(int i = 0; i < 31; i++) {
        int d = 1 << i;
        int contained = 0;
        vector<pair<int,int>> events;

        for(auto p : a) {
            if(p.second - p.first + 1 >= d) {//completely contained
                contained++;
            } else {
                if(p.second % d >= p.first % d) {
                    //right endpoint is after left endpoint, do normally
                    events.push_back({p.first % d,1});
                    events.push_back({p.second % d + 1,-1});
                } else { //right endpoint is after left endpoint, do swap swap
                    events.push_back({p.first % d, 1});
                    events.push_back({d,-1});
                    events.push_back({0,1});
                    events.push_back({p.second%d+1,-1});
                }
            }
        }

        int best = contained;
        int curr = 0;
        sort(events.begin(), events.end());
        for(auto event : events) {
            curr += event.second;
            best = max(best,contained + curr);
        }
        res[i] = best;
    }

    // cout << "res : " << res << '\n';

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int w; cin >> w;
        int d = 0;
        while(w % 2 == 0) {
            w /= 2;
            d++;
        }
        cout << res[d] << "\n";
    }

    return 0;
}