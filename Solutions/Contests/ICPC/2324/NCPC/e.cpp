#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

ll try1(vector<pair<ll,ll>> v, ll modeidx) {
    ll time = 0;
    int n = v.size();
    int i = 0;
    // cout << "try1 time \n";
    // cout << "v before : " << v << '\n';
    for(; i < n; i++) {
        if(i != modeidx && v[i].second) {
            break;
        }
    }
    int j = i + 1;
    for(; j < n; j++) {
        if(j != modeidx && v[j].second) {
            break;
        }
    }
    time += max(v[i].first, v[j].first);
    v[i].second--;
    v[j].second--;

    // cout << "i : " << i << " j : " << j << '\n';

    // cout << "time : " << time << '\n';
    // cout << "v after : " << v << '\n';

    for(int i = 0; i < n; i++) {
        if(i != modeidx) {
            // cout << "i : " << i << " p : " << v[i] << '\n';
            time += max(v[i].first,v[modeidx].first) * v[i].second;
        }
    }
    // cout << "time ? " << time << '\n';
    time += v[modeidx].first;
    // cout << "try1 time : " << time << '\n';
    return time;
}

ll try2(vector<pair<ll,ll>> v, ll modeidx) {
    ll time = 0;
    int n = v.size();
    for(int i = n - 1; i >= 0; i--) {
        if(i != modeidx && v[i].second) {
            time += v[i].first; 
            v[i].second--;
            break;
        }
    }
    // cout << "time b : " << time << '\n';
    for(int i = 0; i < n; i++) {
        if(i != modeidx) {
            // cout << "i : " << i << " p : " << v[i] << '\n';
            time += max(v[i].first,v[modeidx].first) * v[i].second;
        }
    }
    // cout << "try2 time : " << time << '\n';
    return time;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<ll,ll>> v(n);
    ll left = 0;
    Tree<int> tree(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].second >> v[i].first;
        left += v[i].second;
    }
    sort(v.rbegin(), v.rend());

    for(int i = 0; i < n; i++) {
        tree.update(i,v[i].second);
    }

    //testcase is --- ok
    if(tree.query(0,n) * 2 >= left) {
        ll mode = tree.query(0,n);
        int modeidx = -1;

        for(int i = 0; i < n; i++) {
            if(v[i].second == mode) modeidx = i;
        }
        ll time = 0;
        for(int i = 0; i < n; i++) {
            if(i != modeidx) {
                // cout << "i : " << i << " p : " << v[i] << '\n';
                time += max(v[i].first,v[modeidx].first) * v[i].second;
                v[modeidx].second -= v[i].second;
            }
        }
        time += v[modeidx].first * v[modeidx].second;
        cout << time << '\n';
        return 0;
    }

    //hopefully ok
    int loidx = 0;
    ll time = 0;
    for(int i = 0; i < n; i++) {
        if(v[i].second == 0) continue;
        while(loidx == i || v[loidx].second == 0) loidx++;
        ll most = tree.query(0,n);
        if(most * 2 + 1 >= left) break;
        time += max(v[i].first, v[loidx].first);
        // cout << "i : " << i << " loidx : " << loidx << '\n';
        v[i].second--;
        v[loidx].second--;
        left -= 2;
        tree.update(i,v[i].second);
        tree.update(loidx,v[loidx].second);
        if(v[i].second) i--;
    }

    ll mode = tree.query(0,n);
    int modeidx = -1;

    for(int i = 0; i < n; i++) {
        if(v[i].second == mode) modeidx = i;
    }
    // cout << "v ? " << v << '\n';
    // cout << "modeidx : " << modeidx << " modeval : " << v[modeidx] << '\n';

    if(left & 1) {
        time += min(
            try1(v,modeidx),
            try2(v,modeidx)
        );

    } else {
        for(int i = 0; i < n; i++) {
            if(i != modeidx) {
                // cout << "i : " << i << " p : " << v[i] << '\n';
                time += max(v[i].first,v[modeidx].first) * v[i].second;
            }
        }
    }
    
    cout << time << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n;
//     cin >> n;
//     priority_queue<pair<ll, ll>> q; //{time, amt}
//     for(int i = 0; i < n; i++){
//         ll f, t;
//         cin >> f >> t;
//         q.push({t, f});
//     }
//     ll ans = 0;
//     while(q.size() >= 2){
//         ll t0 = q.top().first;
//         ll f0 = q.top().second;
//         q.pop();
//         ll t1 = q.top().first;
//         ll f1 = q.top().second;
//         q.pop();
//         ll f = min(f0, f1);
//         f0 -= f;
//         f1 -= f;
//         ans += f * max(t0, t1);
//         if(f0 != 0){
//             q.push({t0, f0});
//         }
//         if(f1 != 0){
//             q.push({t1, f1});
//         }
//     }
//     if(q.size() != 0){
//         ans += q.top().first * q.top().second;
//     }
//     cout << ans << "\n";

//     return 0;
// }