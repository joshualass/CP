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

template<typename T>
std::ostream& operator<<(std::ostream& os, unordered_set<T> s) {
    for(auto &x: s) os << x << " | ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<pair<int,int>> v(n);

    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i + 1;
    }

    sort(v.begin(), v.end());

    int bucket_count = v.back().first - 1;
    if(bucket_count == 0) { //all one counts
        for(int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << '\n';
        return 0;
    }

    vector<int> bucket_ends;
    while(v.size() && v.back().first - 1 == bucket_count) {
        bucket_ends.push_back(v.back().second);
        v.pop_back();
    }

    vector<unordered_set<int>> buckets(bucket_count);

    int idx = 0;
    while(v.size()) {
        pair<int,int> p = v.back();
        v.pop_back();
        for(int i = 0; i < p.first; i++) {
            buckets[idx++].insert(p.second);
        }
    }

    if(k > bucket_ends.size() + buckets.back().size()) {
        cout << "-1\n";
        return 0;
    }

    map<int,int> prev_bucket;

    for(int i = buckets.size() - 1; i >= 0; i--) {
        cout << bucket_ends;
        vector<int> curr_bucket(buckets[i].size(),-1);
        map<int,int> new_map;
        // cout << "i : " << i << " buckets[i] : " << buckets[i] << '\n';
        for(auto x : prev_bucket) {
            if(buckets[i].find(x.first) != buckets[i].end()) {
                curr_bucket[x.second] = x.first;
                new_map[x.first] = x.second;
                buckets[i].erase(x.first);
            }
        }
        int idx = 0;
        for(auto x : buckets[i]) {
            while(curr_bucket[idx] != -1) {
                idx++;
            }
            curr_bucket[idx] = x;
            new_map[x] = idx;
        }
        swap(prev_bucket,new_map);
        cout << curr_bucket;
    }

    cout << bucket_ends;
    cout << '\n';
    return 0;
}