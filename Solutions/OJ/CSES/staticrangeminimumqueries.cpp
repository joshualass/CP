// #include <bits/stdc++.h>
// typedef long long ll;
// using namespace std;

// const int N = 2e5;
// int n;
// int t[2 * N];

// void build() {
//     for(int i = n-1; i > 0; --i) {
//         t[i] = min(t[i * 2], t[i * 2 + 1]);
//     }
// }

// void modify(int p, int value) {
//     p += n;
//     t[p] = value;
//     while(p > 1) {
//         t[p / 2] = min(t[p], t[p ^ 1]);
//         p /= 2;
//     }
// }

// int query(int l, int r) {
//     int ans = INT_MAX;
//     l += n;
//     r += n;
//     while(l < r) {
//         if(l % 2 == 1) {
//             ans = min(ans, t[l]);
//             l++;
//         }
//         if(r % 2 == 1) {
//             r--;
//             ans = min(ans,t[r]);
//         }
//         l /= 2;
//         r /= 2;
//     }
//     return ans;
// }
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int q; cin >> n >> q;

//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         t[n + i] = num;
//     }
//     build();

//     for(int i = 0; i < q; i++) {
//         int a, b; cin >> a >> b;
//         cout << query(--a,b) << '\n';
//     }

//     return 0;
// }

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
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int least_significant_bit(int x) {return x & -x;}
    int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
    RMQ() {} //need this to satisfy master goon's requirements
    RMQ (const vector<T>& input) {build(input);}
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
        if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1;
        int y = r / block_size - 1;
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return elements[ans]; //return the value
        // return ans;        //return the index with value
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    RMQ rmq(a);
    for(int i = 0; i < q; i++) {
        int c, d; cin >> c >> d;
        cout << rmq.query(c-1,d-1) << '\n';
        
    }

    return 0;
}