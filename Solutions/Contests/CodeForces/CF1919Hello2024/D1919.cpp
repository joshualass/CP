#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//range minimum query. O(1) query, O(n) build/memory. fast.
template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask;
    vector<int> sparse_table;

    //type of function the table is storing. Currently, it stores the minimum because it returns the minimum index 
    int op(int x, int y) { 
        return elements[x] < elements[y] ? x : y;
    }

    int least_significant_bit(int x) {
        return x & -x;
    }
    
    int most_significant_bit_index(int x) {
        return 31 - __builtin_clz(x);
    }

    // answers the smaller queries given size is <= b. elements[r-size+1..r] using masks
    int small_query(int r, int size = block_size) {
        //get only the 'size' least significant bits from the mask
        //with that, get the most significant set bit
        int dist_from_r = most_significant_bit_index(mask[r] & ((1<<size)-1));
        return r - dist_from_r;
    }

    RMQ() {} //need this to satisfy master goon's requirements

    //constructor
    RMQ (const vector<T>& input): elements(input), n(input.size()), mask(n), sparse_table(n) {
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }

    }

    //query(l,r) returns the element from the minimum of v[l..r]
    //can be updated to return index by changing what we are returning
    T query(int l, int r) {
        //query size <= b
        if(r - l + 1 <= block_size) {
            return elements[small_query(r, r - l + 1)];
            // return small_query(r, r- l + 1);
        }

        //work out the small parts of the answer
        //it's ok for it to overlap and because size > b, we can freely let size of both sides be b
        int ans = op(small_query(l + block_size - 1), small_query(r)); 

        //blocks to query over
        int x = l / block_size + 1;
        int y = r / block_size - 1;

        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }

        return elements[ans];
        // return ans;
    }

    //alternative way to build if can't easily do with constructor or want to reuse
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }

    }

};

bool ok;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void find_zeroes(int l, int r, RMQ<int> &rmq, int offset, vector<int> &zeroes) {
    if(r == l) {
        // cout << "l : " << l << " r : " << r << " query : " << rmq.query(l,r) << '\n';
        if(rmq.query(l,r) == offset) {
            zeroes.push_back(l);
        }
        return;
    }

    if(rmq.query(l,r) == offset) {
        find_zeroes(l, (l + r) / 2, rmq, offset, zeroes);
        find_zeroes((l + r) / 2 + 1, r, rmq, offset, zeroes);
    }
}

void dfs(int l, int r, RMQ<int> &rmq, int offset) {
    vector<int> zeroes;
    find_zeroes(l, r, rmq, offset, zeroes);
    // cout << "l : " << l << " r : " << r << " offset : " << offset << " zeroes : " << zeroes << '\n';
    if(zeroes.size() == 0) { //no new zeroes
        ok = 0;
        return;
    }
    assert(is_sorted(zeroes.begin(), zeroes.end()));
    if(zeroes[0] != l) {
        dfs(l,zeroes[0]-1,rmq,offset + 1);
    }
    if(zeroes[zeroes.size()-1] != r) {
        dfs(zeroes[zeroes.size()-1] + 1, r, rmq, offset + 1);
    }
    for(int i = 0; i < zeroes.size() - 1; i++) {
        if(zeroes[i] != zeroes[i+1] - 1) {
            dfs(zeroes[i]+1,zeroes[i+1]-1,rmq,offset+1);
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    ok = 1;

    RMQ<int> rmq(v);

    dfs(0,n - 1,rmq,0);
    if(count(v.begin(),v.end(),0) != 1) ok = 0;

    cout << (ok ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template <typename T>
// struct SegtreeLazy {
//     public:
//         int n;
//         T* t;    //stores product of range
//         T* d;    //lazy tree
//         bool* upd;  //marks whether or not a lazy change is here
//         T uneut, qneut;

//         //single element modify
//         function<T(T, T)> fmodify;

//         //k element modify
//         function<T(T, T, int)> fmodifyk;

//         //product of two elements for query
//         function<T(T, T)> fcombine;

//         SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
//             n = maxSize;
//             uneut = updateNeutral;
//             qneut = queryNeutral;

//             this -> fmodify = fmodify;
//             this -> fmodifyk = fmodifyk;
//             this -> fcombine = fcombine;

//             //raise n to nearest pow 2
//             int x = 1;
//             while(x < n) {
//                 x <<= 1;
//             }
//             n = x;

//             t = new T[n * 2];
//             d = new T[n * 2];
//             upd = new bool[n * 2];

//             //make sure to initialize values
//             for(int i = 0; i < n * 2; i++){
//                 t[i] = uneut;
//             }
//             for(int i = 0; i < n * 2; i++){
//                 d[i] = uneut;
//                 upd[i] = false;
//             }
//         }

//         void modify(int l, int r, T val) {    //modifies the range [l, r)
//             _modify(l, r, val, 0, n, 1);
//         }

//         void modify(int ind, T val) { //modifies the range [ind, ind + 1)
//             _modify(ind, ind + 1, val, 0, n, 1);
//         }

//         T query(int l, int r) {   //queries the range [l, r)
//             return _query(l, r, 0, n, 1);
//         }

//         T query(int ind) {    //queries the range [ind, ind + 1)
//             return _query(ind, ind + 1, 0, n, 1);
//         }

//     private:
//         //calculates value of node based off of children
//         //k is the amount of values that this node represents. 
//         void combine(int ind, int k) {
//             if(ind >= n){
//                 return;
//             }
//             int l = ind * 2;
//             int r = ind * 2 + 1;
//             //make sure children are correct value before calculating
//             push(l, k / 2);
//             push(r, k / 2);
//             t[ind] = fcombine(t[l], t[r]);
//         }

//         //registers a lazy change llo this node
//         void apply(int ind, T val) {
//             upd[ind] = true;
//             d[ind] = fmodify(d[ind], val);
//         }

//         //applies lazy change to this node
//         //k is the amount of values that this node represents. 
//         void push(int ind, int k) {
//             if(!upd[ind]) {
//                 return;
//             }
//             t[ind] = fmodifyk(t[ind], d[ind], k);
//             if(ind < n) {
//                 int l = ind * 2;
//                 int r = ind * 2 + 1;
//                 apply(l, d[ind]);
//                 apply(r, d[ind]);
//             }
//             upd[ind] = false;
//             d[ind] = uneut;
//         }

//         void _modify(int l, int r, T val, int tl, int tr, int ind) {
//             if(l == r){
//                 return;
//             }
//             if(upd[ind]) {
//                 push(ind, tr - tl);
//             }
//             if(l == tl && r == tr) {
//                 apply(ind, val);
//                 push(ind, tr - tl);
//                 return;
//             }
//             int mid = tl + (tr - tl) / 2;
//             if(l < mid) {
//                 _modify(l, min(r, mid), val, tl, mid, ind * 2);
//             }
//             if(r > mid) {
//                 _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
//             }
//             combine(ind, tr - tl);
//         }

//         T _query(int l, int r, int tl, int tr, int ind) {
//             if(l == r){
//                 return qneut;
//             }  
//             if(upd[ind]) {
//                 push(ind, tr - tl);
//             }
//             if(l == tl && r == tr){
//                 return t[ind];
//             }
//             int mid = tl + (tr - tl) / 2;
//             T lans = qneut;
//             T rans = qneut;
//             if(l < mid) {
//                 lans = _query(l, min(r, mid), tl, mid, ind * 2);
//             }
//             if(r > mid) {
//                 rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
//             }
//             return fcombine(lans, rans);
//         }
// };

// void solve() {
//     ll n; cin >> n;
//     vector<ll> v(n);
//     for(ll &x : v) cin >> x;
    
//     function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
//     function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
//     function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return min(a, b);};

//     SegtreeLazy<ll> duckduckgo(n,0,0,modifyElement,modifyRange,queryType);

//     for(int i = 0; i < n; i++) {
//         duckduckgo.modify(i,v[i]);
//     }

//     ll ops = 0;
//     bool poss = 1;
//     int loidx = 0;
//     while(true) {
//         if(loidx =)

//         if(ops >= n) {
//             poss = 0;
//             break;
//         }
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }