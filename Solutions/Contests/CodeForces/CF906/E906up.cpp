#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<pair<int,int>> ranges(m);
    vector<vector<int>> events;
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        ranges[i] = {l,r};
        events.push_back({l, 1, i});
        events.push_back({r+1,-1,i});
    }

    sort(events.begin(), events.end());

    vector<int> pref(n+1);
    int idx = 0;
    int curr = 0;
    for(int i = 0; i < n; i++) {
        while(idx < events.size() && events[idx][0] == i) {
            curr += events[idx++][1];
        }
        pref[i+1] = curr;
    }

    vector<int> prefones(n+1);
    vector<int> preftwos(n+1);
    int zerocount = 0;
    for(int i = 0; i < n; i++) {
        prefones[i+1] = prefones[i] + (pref[i+1] == 1);
        preftwos[i+1] = preftwos[i] + (pref[i+1] == 2);
        zerocount += (pref[i+1] == 0);
    }

    priority_queue<int, vector<int>, greater<int>> pq; //pq, by default, is a max heap :)

    for(int i = 0; i < m; i++) {
        int num = prefones[ranges[i].second + 1] - prefones[ranges[i].first];
        if(pq.size() < 2) {
            pq.push(num);
        } else if(pq.top() < num) {
            pq.pop();
            pq.push(num);
        }
    }

    int best_disjoint = pq.top();
    pq.pop();
    best_disjoint += pq.top();

    // vector<int> disjoints(m);
    // for(int i = 0; i < m; i++) {
    //     int num = prefones[ranges[i].second + 1] - prefones[ranges[i].first];
    //     disjoints[i] = num;
    // }

    // sort(disjoints.begin(), disjoints.end());

    // int best_disjoint = disjoints[m-1] + disjoints[m-2];

    int ans = zerocount + best_disjoint;

    // cout << "prefs: " << pref << '\n';
    // cout << "zerocount: " << zerocount << '\n';
    // cout << "prefones: " << prefones << '\n';
    // cout << "preftwos: " << preftwos << '\n';
    // cout << "best disjoint: " << best_disjoint << '\n';
    // cout << "ans: " << ans << '\n';

    set<int> active;
    idx = 0;
    for(int i = 0; i < n; i++) {
        while(idx < events.size() && events[idx][0] == i) {
            if(events[idx][1] == 1) {
                active.insert(events[idx][2]);
            } else {
                active.erase(events[idx][2]);
            }
            idx++;
        }

        if(active.size() == 2) {
            pair<int,int> first = ranges[*active.begin()];
            pair<int,int> second = ranges[*next(active.begin())];
            int lo = prefones[max(first.first, second.first) + 1] - prefones[min(first.first, second.first)];
            int mid = preftwos[min(first.second, second.second) + 1] - preftwos[max(first.first, second.first)];
            int hi = prefones[max(second.second, first.second) + 1] - prefones[min(first.second, second.second)];
            if(zerocount + lo + mid + hi > ans) {
                // cout << "updating answer...\n";
                // cout << "ranges: " << (*active.begin()) << " and " << (*next(active.begin())) << '\n';
            }
            ans = max(ans, zerocount + lo + mid + hi);
        }
    }

    cout << ans << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}