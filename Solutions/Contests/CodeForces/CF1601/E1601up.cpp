#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

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
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//range minimum query. O(1) query, O(n) build/memory. fast.
template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask, sparse_table;
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
        int x = l / block_size + 1, y = r / block_size - 1;
        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return elements[ans]; //return the value
        // return ans;        //return the index with value
    }
};

vector<ll> solve(int n, int q, int k, vector<int> a, vector<array<int,2>> queries) {

    RMQ<int> rmq(a);
    vector<vector<vector<array<int,2>>>> qs(k, vector<vector<array<int,2>>>((n + k - 1) / k));
    vector<ll> res(q);

    for(int qq = 0; qq < q; qq++) {
        auto [l, r] = queries[qq];
        l--;
        res[qq] += a[l];
        int len = r - l;
        int ints = (len - 1) / k;
        l++;
        int kb = l % k;
        int lb  = l / k;
        if(ints) {
            qs[kb][lb].push_back({ints, qq});
        }
    }
    
    auto append = [&](vector<array<ll,4>> &st, ll rate) -> void {
        assert(!st.empty());
        ll len = 1, cost = rate;
        while(!st.empty() && st.back()[1] >= rate) {
            auto [ptotallen, pr, plen, pcost] = st.back();
            st.pop_back();
            cost += rate * plen;
            len += plen;
        }
        st.push_back({len + st.back()[0], rate, len, cost + st.back()[3]});
    };
    
    auto query = [&](vector<array<ll,4>> &st, ll qlen) -> ll {
        assert(st.back()[0] >= qlen);
        int idx = lower_bound(st.begin(), st.end(), array<ll,4>{st.back()[0] - qlen, 0, 0, 0}) - st.begin();
        ll cost = st.back()[3] - st[idx][3] + st[idx][1] * (qlen - (st.back()[0] - st[idx][0]));
        return cost;
    };
    
    for(int i = 0; i < k; i++) {
        vector<array<ll,4>> st(1);
        for(int j = (n + k - 1) / k - 1; j >= 0; j--) {
            int l = i + j * k;
            int r = l + k;
            if(r <= n) {
                append(st, rmq.query(l - 1, r - 1));
                for(auto [len, qidx] : qs[i][j]) {
                    res[qidx] += query(st, len);
                }
            } else {
                assert(qs[i][j].empty());
            }
        }
    }

    return res;
}

vector<ll> solve_slow(int n, int q, int k, vector<int> a, vector<array<int,2>> queries) {
    vector<ll> res;
    for(int i = 0; i < q; i++) {
        auto [l, r] = queries[i];
        l--;
        ll cost = 0;
        int min_cost = inf;
        for(int i = l; i < r; i++) {
            min_cost = min(min_cost, a[i]);
            if((i - l) % k == 0) cost += min_cost;
        }
        res.push_back(cost);
    }
    return res;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);



    for(int i = 0; i < 10000; i++) {
        int n = 5, q = 5;
        int k = rng() % n + 1;
        vector<int> a(n);
        for(int &x : a) x = rng() % 10 + 1;
        vector<array<int,2>> queries;
        for(int j = 0; j < q; j++) {
            int l = rng() % n, r = rng() % n;
            if(l > r) swap(l, r);
            l++; r++;
            queries.push_back({l, r});
        }
        auto res_slow = solve_slow(n, q, k, a, queries);
        auto res_fast = solve(n, q, k, a, queries);
        if(res_slow != res_fast) {
            cout << n << " " << q << " " << k << endl;
            for(int j = 0; j < n; j++) {
                cout << a[j] << " \n"[j == n - 1];
            }
            for(auto query : queries) {
                cout << query[0] << " " << query[1] << endl;
            }
            cout << "slow (correct?) : " << res_slow << endl;
            cout << "fast : " << res_fast << endl;
            assert(0);
        }
    }

    cout << "ALL TESTS PASSED!" << endl;

    return 0;
}
