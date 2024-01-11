#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 4e5;
int dsu[N];
int depths[N];
int sizes[N];

int find(int x) {
    if(dsu[x] == x) {
        return x;
    }
    dsu[x] = find(dsu[x]);
    return dsu[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y) {
        return;
    }
    if(sizes[x] == sizes[y]) {
        dsu[y] = x;
        depths[x]++;
        sizes[x] += sizes[y];
    } else if(sizes[x] < sizes[y]) {
        dsu[y] = x;
        sizes[x] += sizes[y];
    } else {
        dsu[x] = y;
        sizes[y] += sizes[x];
    }
}

template<typename T>
struct SegTreeMIQ { //SegTree Minimum Index query. Finds the minimum index that satisfies cond. 
    static constexpr T base = 0; //change this when doing maximum vs minimum etc.
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b); 
    }

    bool cond(T a, T b) { //num, array value
        return a <= b; //change this when doing maximum vs minimum etc.
    }
    vector<T> v;
    int n = -1, size = -1;

    SegTreeMIQ(int n = 0, T def = base) {
        this->n = n; //max number of elements
        this->size = 1 << (31 - __countl_zero(n) - (int)(__builtin_popcount(n) == 1)); //size of vector
        v.assign(size * 2, base);
    }

    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            v[curr/2] = comb(v[curr], v[curr ^ 1]);
            curr /= 2;
        }
    }

    bool isLeaf(int idx) {
        return idx >= size;
    }

    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }

    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> query(T val, int lo, int hi) {
        if(lo >= hi) return {-1,base}; //starting pos is OOB
        lo = max(lo,0);
        hi = min(hi,n);
        pair<int,T> ans = _query(1, lo, hi, val);
        return ans;
    }   

    pair<int,T> query(T val, int lo) {
        return query(val,lo,n);
    }   

    pair<int,T> query(T val) {
        return query(val, 0, n);
    }

    pair<int,T> _query(int idx, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(isLeaf(idx)) {
            if(cond(val, v[idx])) { // in case length is 1 and index is invalid
                return {idx - size, v[idx]};
            } else {
                return {-1,base};
            }
        }
        int shift = __countl_zero(idx) - __countl_zero(size);
        int left_lo = (idx << shift) - size;
        int left_hi = left_lo + (1 << (shift - 1));
        int right_lo = left_hi;
        int right_hi = right_lo + (1 << (shift - 1));

        //overlap in left and an answer exists, doesn't necessarily mean a solution
        if(left_hi > lo && cond(val, v[idx * 2])) {
            // cout << " go left \n";
            pair<int,T> ans = _query(idx * 2, lo, hi, val);
            if(ans.first != -1) return ans;
        }
        //overlap in right and an answer exists
        if(right_lo < hi && cond(val, v[idx * 2 + 1])) {
            // cout << " go right \n";
            return _query(idx * 2 + 1, lo, hi, val);
        }

        return {-1,base}; //nooverlap in both sides/doesn't exist
    }
};

void solve() {
    int n; cin >> n;
    for(int i = 0; i < n * 2; i++) {
        dsu[i] = i;
        depths[i] = 1;
        sizes[i] = 1;
    }
    vector<pair<int,int>> ranges(n,{-1,-1});
    SegTreeMIQ<int> tree(n * 2);
    for(int i = 0; i < n * 2; i++) {
        int num; cin >> num;
        num--;
        if(ranges[num].first != -1) {
            ranges[num].second = i;
            tree.update(ranges[num].first, ranges[num].second);
            merge(ranges[num].first, ranges[num].second);
            // cout << "initial merges : " << ranges[num].first << " " << ranges[num].second << '\n';
        } else {
            ranges[num].first = i;
        }
    }
    sort(ranges.begin(), ranges.end());
    vector<vector<pair<int,int>>> upd_ranges(0);
    int hi = -1;
    for(int i = 0; i < n; i++) {
        if(ranges[i].first > hi) {
            upd_ranges.push_back({});
        }
        hi = max(hi, ranges[i].second);
        upd_ranges.back().push_back(ranges[i]);
    }
    ll ans = 1;
    int comps = 0;
    for(int i = 0; i < upd_ranges.size(); i++) {
        comps++;
        queue<pair<int,int>> q;
        q.push(upd_ranges[i][0]);
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            pair<int,int> query = tree.query(p.second, p.first + 1, p.second);
            while(query.first != -1) {
                merge(upd_ranges[i][0].first, query.first);
                // cout << "merging : " << upd_ranges[i][0].first << " with : " << query.first << '\n';
                tree.update(query.first,0);
                q.push({query.first, query.second});
                query = tree.query(p.second, p.first + 1, p.second);
            }
            query = tree.query(p.first, 0, p.first);
            while(query.first != -1) {
                merge(upd_ranges[i][0].first, query.first);
                // cout << "merging : " << upd_ranges[i][0].first << " with : " << query.first << '\n';
                tree.update(query.first,0);
                q.push({query.first, query.second});
               query = tree.query(p.first, 0, p.first);
            }
        }
        ans *= sizes[find(upd_ranges[i][0].first)];
        ans %= MOD;
        // sort(upd_ranges[i].begin(), upd_ranges[i].end(), [] (pair<int,int> &lhs, pair<int,int> &rhs) -> bool {
        //     return lhs.second - lhs.first < rhs.second - rhs.first;;
        // });
        // set<int> visited;
        // comps++;
        // int cnt = upd_ranges[i].size();
        // set<pair<int,int>> s;
        // int lo = INT_MAX;
        // int hi = INT_MIN;
        
        // for(int j = 0; j < upd_ranges[i].size(); j++) {
        //     s.insert(upd_ranges[i][j]);
        //     lo = min(lo, upd_ranges[i][j].first);
        //     hi = max(hi,upd_ranges[i][j].second);
        // }
        // int cnt = upd_ranges[i].size();
        // for(int j = lo; j <= hi; j++) {
        //     int lp = j, hp = j + 1;
        //     while(s.count({lp,hp})) {
        //         cnt--;
        //         lp--;
        //         hp++;
        //     }
        // }
        // for(pair<int,int> range : upd_ranges[i]) {
        //     if(range.second - range.first == 1 || visited.count(range.first+1) && visited.count(range.second - 1)) {
        //         visited.insert(range.first);
        //         visited.insert(range.second);
        //         cnt--;
        //     }
        // }
        // ans *= max(2,cnt*2);
        // ans %= MOD;
    }
    cout << comps << " " << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}