#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 1e9;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
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
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n - 1);
    for(int &x : a) cin >> x;
    int m; cin >> m;
    vector<array<int,2>> b(m);
    for(auto &x : b) {
        cin >> x[0] >> x[1];
        x[0]--; x[1]--;
    }

    sort(b.begin(), b.end());
    vector<array<int,2>> ranges;
    for(array<int,2> range : b) {
        while(ranges.size() && ranges.back()[1] >= range[1]) {
            ranges.pop_back();
        }
        if(ranges.empty() || range[0] > ranges.back()[0]) {
            ranges.push_back(range);
        }
    }

    // cout << "ranges : " << ranges << '\n';

    Tree<int> tree(ranges.size() + 1);
    tree.update(0, 0);
    int l = -1, r = -1;

    for(int i = 0; i < n - 1; i++) {
        while(r + 1 < ranges.size() && ranges[r+1][1] > i && ranges[r+1][0] <= i) r++;
        while(l + 1 < ranges.size() && ranges[l+1][1] <= i) l++;
        // cout << "i : " << i << " l : " << l << " r : " << r << '\n';
        // cout << "updating to pos : " << r + 1 << " with value : " << min(tree.at(r + 1), a[i] + tree.query(l + 1, ranges.size() + 1)) << '\n';
        tree.update(r + 1, min(tree.at(r + 1), a[i] + tree.query(l + 1, ranges.size() + 1)));
    }

    cout << tree.at(ranges.size()) << '\n';

    return 0;
}