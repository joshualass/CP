#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i+1;
    }
    vector<int> b(m);
    for(int &x : b) cin >> x;
    sort(v.begin(), v.end());
    // cout << "v : " << v << '\n';
    vector<RMQ<pair<int,int>>> rmqs;
    for(int i = 0; i < m; i++) {
        vector<pair<int,int>> a;
        for(int j = 0; j < n; j++) {
            int skill = v[j].first;
            int needed = (b[i] + skill - 1) / skill;
            a.push_back({j + needed,j});
        }
        // cout << "b[i] : " << b[i] << " a : " << a << '\n';
        rmqs.push_back(RMQ<pair<int,int>>(a));
    }

    vector<pair<pair<int,int>,int>> dp(1 << m,{{-1,-1},-1});
    dp[0] = {{0,0},-1};

    //pull dp. wa? wa because it may not be optimal to use the programmer with lowest tolerance. at all. 
    for(int i = 1; i < 1 << m; i++) {
        for(int bit = 0; bit < m; bit++) {
            if((i >> bit) & 1) {
                int lo = dp[i ^ (1 << bit)].first.first;
                if(lo != -1 && lo != n) {
                    int skill = v[lo].first;
                    int needed = (b[bit] + skill - 1) / skill;
                    pair<int,int> mi = rmqs[bit].query(lo,n-1);
                    if(mi.first <= n && (dp[i].first.first == -1 || dp[i].first.first != -1 && dp[i].first.first > mi.first)) {
                        dp[i] = {mi, bit};
                    }
                }
            }
        }
    }
    //push dp
    // for(int i = 0; i < 1 << m; i++) {
    //     if(dp[i].first == -1 || dp[i].first == n) continue;
    //     int lo = dp[i].first;
    //     for(int bit = 0; bit < m; bit++) {
    //         if(((i >> bit) & 1) == 0) {
    //             int to = i ^ (1 << bit);
    //             int skill = v[lo].first;
    //             int needed = (b[bit] + skill - 1) / skill;
    //             if(needed + lo <= n && (dp[to].first == -1 || dp[to].first != -1 && needed + lo < dp[to].first)) {
    //                 dp[to] = {needed + lo, bit};
    //             }
    //         }
    //     }
    // }

    // cout << "dp\n";
    // for(auto p : dp) cout << p << '\n';

    if(dp.back() != make_pair(make_pair(-1,-1),-1)) {
        cout << "Yes\n";
        int c = (1 << m) - 1;
        vector<vector<int>> o(m);
        while(1) {
            int p = c ^ (1 << dp[c].second);
            // cout << "p : " << dp[c] << '\n';
            // cout << prev - dp[p].first << " ";
            // for(int i = dp[p].first; i < dp[c].first; i++) {
            //     cout << v[i].second << " \n"[i == prev - 1];
            //     o[dp[c].second].push_back(v[i].second);
            // }
            for(int i = dp[c].first.second; i < dp[c].first.first; i++) {
                o[dp[c].second].push_back(v[i].second);
            }
            if(p == 0) break;
            c = p;
        }
        for(vector<int> v: o) {
            cout << v.size() << " ";
            for(int i = 0; i < v.size(); i++) {
                cout << v[i] << " \n"[i == v.size() - 1];
            }
        }
    } else {
        cout << "No\n";
    }
    return 0;
}