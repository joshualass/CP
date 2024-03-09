#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
    }
    // optional MIQ stuff
    bool cond(T a, T b) {
        return a <= b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //non
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
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
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
        pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
        return ans;
    }   
    pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(cond(val, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (currl + currr) / 2;
            if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
            return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        } else {
            return {-1,base};
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> lpq;
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<pair<int,int>> ranges(m);
    for(auto &x : ranges) {
        cin >> x.first >> x.second;
        x.first--, x.second--;
    }
    sort(ranges.begin(), ranges.end());
    Tree<int> tree(n);

    int loidx = 0;
    for(int i = 0; i < n; i++) {
        while(loidx != m && ranges[loidx].first <= i) {
            lpq.push({ranges[loidx].first,loidx});
            pq.push(ranges[loidx].second);
            loidx++;
        }
        while(lpq.size() && ranges[lpq.top().second].second < i) {
            lpq.pop();
        }
        while(pq.size() && pq.top() < i) {
            pq.pop();
        }
        
        int lq = (lpq.size() ? lpq.top().first : i);
        int loval = tree.query(0,lq);
        // cout << "i : " << i << " lq : " << lq << " loval : " << loval << " active : " << pq.size() << " hi : " << hi << '\n';
        tree.update(i, pq.size() + loval);
        
    }
    cout << tree.query(0,n) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}