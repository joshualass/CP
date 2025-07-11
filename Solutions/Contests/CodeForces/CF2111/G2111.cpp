//better DS 
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

set<pii>::iterator addInterval(set<pii>& is, int L, int R) {
	if (L == R) return is.end();
	auto it = is.lower_bound({L, R}), before = it;
	while (it != is.end() && it->first <= R) {
		R = max(R, it->second);
		before = it = is.erase(it);
	}
	if (it != is.begin() && (--it)->second >= L) {
		L = min(L, it->first);
		R = max(R, it->second);
		is.erase(it);
	}
	return is.insert(before, {L,R});
}

void removeInterval(set<pii>& is, int L, int R) {
	if (L == R) return;
	auto it = addInterval(is, L, R);
	auto r2 = it->second;
	if (it->first == L) is.erase(it);
	else (int&)it->second = L;
	if (R != r2) is.emplace(R, r2);
}

int isContained(set<pii>& is, int L, int R) {
    auto it = is.lower_bound({L, INT_MAX});
    if(it != is.begin()) {
        it--;
        return it->second >= R;
    }
    return 0;
}

//supports 2 operations
template<typename T>
struct InvertedTree {
    vector<set<T>> s; int n;
    InvertedTree(int n, set<T> def) : s(n*2,def), n(n) {}
    void update(int l, int r, T u) { //increases values in [l,r) by u
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                // s[l] = f(s[l],u);
                addInterval(s[l], u.first, u.second);
                l++;
            }
            if(r & 1) {
                r--;
                // s[r] = f(s[r],u);
                addInterval(s[r], u.first, u.second);
            }
        }
    }
    int query(int pos, int r) { //queries the value of element at pos
        // T ans = s[pos += n];
        int ans = 0;
        ans |= isContained(s[pos += n], r, r + 1);
        while(pos /= 2) {
            // ans = f(ans,s[pos]);
            ans |= isContained(s[pos], r, r + 1);
        }
        return ans;
    }
};

template<typename T>
struct MinTree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    MinTree(int n = 0, T def = base) {
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
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node < query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
    pair<int,T> find_last(int l, int r, T query_val) {
        return _find_last(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
            if(p.first != -1) {
                return p;
            }
            return _find_last(idx * 2, cl, mid, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
};

template<typename T>
struct MaxTree {
    static constexpr T base = INT_MIN;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    MaxTree(int n = 0, T def = base) {
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
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node > query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
    pair<int,T> find_last(int l, int r, T query_val) {
        return _find_last(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
            if(p.first != -1) {
                return p;
            }
            return _find_last(idx * 2, cl, mid, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
};

/*
general find first logic
just like a query, make sure there is some overlap
then see if there is anything good in interval to keep pursuing
if so, see if done if leaf else, try the greedy sides. 
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    InvertedTree<pii> iTree(n, {});

    auto add_rect = [&](int ll, int lr, int rl, int rr) -> void {
        iTree.update(ll, lr, {rl, rr});
    };

    MaxTree<int> maxt(n);
    MinTree<int> mint(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        maxt.update(i, a[i]);
        mint.update(i, a[i]);
    }

    for(int i = 0; i < n; i++) {

        // cout << "i : " << i << '\n';
        
        {   //for the case where <
            // cout << "case < \n";
            auto [ll, trash0] = maxt.find_last(0, i, a[i]);
            ll++;
            auto [lr, trash1] = maxt.find_first(i, n, a[i]);
            int rl = lr;
            auto [rr, trash2] = mint.find_first(rl, n, a[i]);
            add_rect(ll, lr, rl, rr);
        }

        {   //for the case where >
            // cout << "case > \n";
            auto [ll, trash0] = mint.find_last(0, i, a[i]);
            ll++;
            auto [lr, trash1] = mint.find_first(i, n, a[i]);
            int rl = lr;
            auto [rr, trash2] = maxt.find_first(rl, n, a[i]);
            add_rect(ll, lr, rl, rr);
        }
    }


    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--;
        // int idx0 = *--lower_bound(ps[l].begin(), ps[l].end(), r * 2);
        // int idx1 = *--lower_bound(ps[SQN * SQN + l / SQN].begin(), ps[SQN * SQN + l / SQN].end(), r * 2);

        // cout << "cur : " << cur << " cur2 : " << cur2 << '\n';

        // cout << ((idx0 & 1) || (idx1 & 1) ? "YES" : "NO") << endl;

        r--;

        cout << (iTree.query(l, r) ? "YES" : "NO") << endl;

    }

    return 0;
}

/*
YES
YES
YES
YES
NO
NO
NO
YES
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO
YES
YES
YES
YES
YES
YES
YES
YES
YES
YES
YES
YES
YES
YES
NO
NO
YES
YES
YES
YES
YES
YES
*/


// //wrong idea, x does not necessarily equal a[i]. 
// //fix x, then find largest bounding rectangle. adjust rectangle finding logic. 

// #include <bits/stdc++.h>
// using namespace std;

// template<typename T>
// struct MinTree {
//     static constexpr T base = INT_MAX;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return min(a, b);
//     }
//     MinTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
//     }
//     bool cond(T query_val, T tree_node) {
//         return tree_node < query_val;
//     }
//     pair<int,T> find_first(int l, int r, T query_val) {
//         return _find_first(1, 0, size, l, r, query_val);
//     }
//     pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
//         // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
//         if(cr <= tl || cl >= tr) return {n, base};
//         if(cond(qv, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (cl + cr) / 2;
//             auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
//             if(p.first != n){
//                 return p;
//             }
//             return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
//         } else {
//             return {n, base};
//         }
//     }
//     pair<int,T> find_last(int l, int r, T query_val) {
//         return _find_last(1, 0, size, l, r, query_val);
//     }
//     pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
//         if(cr <= tl || cl >= tr) return {-1, base};
//         if(cond(qv, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (cl + cr) / 2;
//             auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
//             if(p.first != -1) {
//                 return p;
//             }
//             return _find_last(idx * 2, cl, mid, tl, tr, qv);
//         } else {
//             return {-1, base};
//         }
//     }
// };

// template<typename T>
// struct MaxTree {
//     static constexpr T base = INT_MIN;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a, b);
//     }
//     MaxTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
//     }
//     bool cond(T query_val, T tree_node) {
//         return tree_node > query_val;
//     }
//     pair<int,T> find_first(int l, int r, T query_val) {
//         return _find_first(1, 0, size, l, r, query_val);
//     }
//     pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
//         // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
//         if(cr <= tl || cl >= tr) return {n, base};
//         if(cond(qv, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (cl + cr) / 2;
//             auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
//             if(p.first != n){
//                 return p;
//             }
//             return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
//         } else {
//             return {n, base};
//         }
//     }
//     pair<int,T> find_last(int l, int r, T query_val) {
//         return _find_last(1, 0, size, l, r, query_val);
//     }
//     pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
//         if(cr <= tl || cl >= tr) return {-1, base};
//         if(cond(qv, v[idx])) {
//             if(isLeaf(idx)) return {idx - size, v[idx]};
//             int mid = (cl + cr) / 2;
//             auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
//             if(p.first != -1) {
//                 return p;
//             }
//             return _find_last(idx * 2, cl, mid, tl, tr, qv);
//         } else {
//             return {-1, base};
//         }
//     }
// };

// /*
// general find first logic
// just like a query, make sure there is some overlap
// then see if there is anything good in interval to keep pursuing
// if so, see if done if leaf else, try the greedy sides. 
// */

// //TODO check that range properly works with tl and tr. only tested for tl = 0 and tr = n. 

// const int SQN = 448;
// vector<int> ps[SQN * SQN + SQN];
// int curs[SQN * SQN + SQN];
// vector<int> upds[SQN * SQN + 1];
// int upd_status[SQN * SQN + SQN];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> a(n);

//     auto add_upd = [&](int lidx, int r, int delta) -> void {
//         assert(lidx >= 0 && lidx < SQN * SQN + SQN);
//         assert(0 <= r && r < SQN * SQN);
//         // upds[r].push_back({lidx, delta});
//         upds[r].push_back((lidx + 1) * delta);
//     };

//     auto add_rect = [&](int ll, int lr, int rl, int rr) -> void {
//         assert(ll >= 0 && ll <= lr && lr <= n && 0 <= rl && rl <= rr && rr <= n);
//         // cout << "ll : " << ll << " lr : " << lr << " rl : " << rl << " rr : " << rr << endl;
//         int early_complete = (ll + SQN - 1) / SQN;
//         int late_complete = lr / SQN;

//         for(int i = early_complete; i < late_complete; i++) {
//             add_upd(SQN * SQN + i, rl, 1);
//             add_upd(SQN * SQN + i, rr, -1);
//         }

//         for(int i = ll; i < early_complete * SQN && i < lr; i++) {
//             add_upd(i, rl, 1);
//             add_upd(i, rr, -1);
//         }

//         for(int i = lr - 1; i >= late_complete * SQN && i >= ll && i >= min(early_complete * SQN, lr); i--) {
//             add_upd(i, rl, 1);
//             add_upd(i, rr, -1);
//         }

//     };

//     MaxTree<int> maxt(n);
//     MinTree<int> mint(n);

//     for(int i = 0; i < n; i++) {
//         cin >> a[i];
//         maxt.update(i, a[i]);
//         mint.update(i, a[i]);
//     }

//     for(int i = 0; i < n; i++) {

//         // cout << "i : " << i << '\n';
        
//         {   //for the case where <
//             // cout << "case < \n";
//             auto [ll, trash0] = maxt.find_last(0, i, a[i]);
//             ll++;
//             auto [lr, trash1] = maxt.find_first(i, n, a[i]);
//             int rl = lr;
//             auto [rr, trash2] = mint.find_first(rl, n, a[i]);
//             add_rect(ll, lr, rl, rr);
//         }

//         {   //for the case where >
//             // cout << "case > \n";
//             auto [ll, trash0] = mint.find_last(0, i, a[i]);
//             ll++;
//             auto [lr, trash1] = mint.find_first(i, n, a[i]);
//             int rl = lr;
//             auto [rr, trash2] = maxt.find_first(rl, n, a[i]);
//             add_rect(ll, lr, rl, rr);
//         }
//     }

//     for(int i = 0; i < SQN * SQN + SQN; i++) ps[i].push_back(-2);

//     for(int i = 0; i < n; i++) {
//         vector<int> check_status;
//         // for(auto [idx, delta] : upds[i]) {
//         for(int info : upds[i]) {
//             int delta = info > 0 ? 1 : -1;
//             int idx = abs(info) - 1;
//             // cout << "idx : " << idx << " delta : " << delta << endl;
//             assert(0 <= idx && idx < SQN * SQN + SQN);
//             curs[idx] += delta;
//             if(upd_status[idx] == 0) {
//                 check_status.push_back(idx);
//                 upd_status[idx] = 1;
//             }
//         }
//         upds[i].clear();
//         for(int x : check_status) {
//             assert(0 <= x && x < SQN * SQN + SQN);
//             upd_status[x] = 0;
//             ps[x].push_back(i * 2 + ((int) (curs[x] > 0)));
//         }
//     }

//     int q; cin >> q;
//     for(int i = 0; i < q; i++) {
//         int l, r; cin >> l >> r;
//         l--;
//         int idx0 = *--lower_bound(ps[l].begin(), ps[l].end(), r * 2);
//         int idx1 = *--lower_bound(ps[SQN * SQN + l / SQN].begin(), ps[SQN * SQN + l / SQN].end(), r * 2);

//         // cout << "cur : " << cur << " cur2 : " << cur2 << '\n';

//         cout << ((idx0 & 1) || (idx1 & 1) ? "YES" : "NO") << endl;
//     }

//     return 0;
// }
