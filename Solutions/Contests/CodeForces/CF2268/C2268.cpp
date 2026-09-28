#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int depth = 18;
const int debug = 0;
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

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

// //range minimum query. O(1) query, O(n) build/memory. fast.
// template<typename T>
// struct RMQ  {
//     vector<T> elements;
//     int n;
//     static const int block_size = 30; // block size. adjust accordingly
//     vector<int> mask, sparse_table;
//     int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
//         return elements[x] > elements[y] ? x : y;
//     }
//     int least_significant_bit(int x) {return x & -x;}
//     int most_significant_bit_index(int x) {return 31 - __builtin_clz(x);}
//     int small_query(int r, int size = block_size) {return r - most_significant_bit_index(mask[r] & ((1<<size)-1));}
//     RMQ() {} //need this to satisfy master goon's requirements
//     RMQ (const vector<T>& input) {build(input);}
//     void build (const vector<T>& input) {
//         elements = input;
//         n = input.size();
//         mask.assign(n,0);
//         sparse_table.assign(n,0);
//         int curr_mask = 0;
//         for(int i = 0; i < n; i++) {
//             curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
//             while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) curr_mask ^= least_significant_bit(curr_mask);
//             curr_mask |= 1;
//             mask[i] = curr_mask;
//         }
//         for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
//         for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
//     }
//     T query(int l, int r) {//query(l,r) returns the element from the minimum of v[l..r]
//         if(r - l + 1 <= block_size) return elements[small_query(r, r - l + 1)];
//         int ans = op(small_query(l + block_size - 1), small_query(r)); 
//         int x = l / block_size + 1, y = r / block_size - 1;
//         if(x <= y) {
//             int j = most_significant_bit_index(y - x + 1);
//             ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
//         }
//         // return elements[ans]; //return the value
//         return ans;        //return the index with value
//     }
// };

template<typename T>
struct sparse {
    vector<vector<T>> sparsetable;
    int n, d;
    sparse() {}
    sparse(vector<T> a) {
        buildTable(a);
    }
    T op(T a, T b) {
        return max(a,b);
    }
    void buildTable(vector<T> a) {
        n = a.size();
        d = 32 - __builtin_clz(n);
        sparsetable.assign(n, vector<T>(d));
        for(int depth = 0; depth < d; depth++) {
            for(int i = 0; i < n; i++) {
                if(depth) {
                    sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
                } else {
                    sparsetable[i][depth] = a[i];
                }
            }
        }
    }
    //[l,r) always. 
    T query(int l, int r) {
        r++;
        int depth = 31 - __builtin_clz(r - l);
        return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
    }
};

struct trie {

    vector<array<array<int,2>, 2>> a;
    int t = 0, stop, bestbm;
    array<array<int,2>, 2> def = array<array<int,2>, 2>{array<int,2>{-1,-1},array<int,2>{-1,-1}};
    trie(int stop, int bestbm) : stop(stop), bestbm(bestbm) {
        // cout << "create trie" << endl;
        a.push_back(def);
    }

    void insert(int x, int time) {
        // cout << "insert x : " << x << " time : " << time << endl;
        x &= bestbm;

        int temp = x;
        x ^= t;
        t ^= temp;

        int cur = 0;

        // cout << "tx : " << x << endl;

        for(int i = depth - 1; i >= stop; i--) {
            int bit = (x >> i) & 1;
            if(((bestbm >> i) & 1) == 0) {
                bit = 0;
            }
            // cout << "i : " << i << " bit : " << bit << endl;
            if(a[cur][bit][0] == -1) {
                int nx = sz(a);
                a.push_back(def);
                a[cur][bit][0] = nx;
            }
            a[cur][bit][1] = time;
            cur = a[cur][bit][0];
        }
    }

    int query(int x, int r) {
        // cout << "query x : " << x << " r : " << r << endl;
        x &= bestbm;
        // cout << "t : " << t << endl;
        x ^= t;
        // cout << "tx : " << x << endl;

        int cur = 0, res = 0;
        for(int i = depth - 1; i >= stop; i--) {
            if((bestbm >> i) & 1) {
                int bit = ((x >> i) & 1) ^ 1;
                // cout << "i : " << i << " bit : " << bit << endl;
                // cout << "box : " << a[cur] << endl;
                if(a[cur][bit][0] != -1 && a[cur][bit][1] <= r) {
                    // cout << "hit!" << endl;
                    res += 1 << i;
                    cur = a[cur][bit][0];
                } else {
                    // cout << "miss" << endl;
                    assert(a[cur][bit ^ 1][0] != -1);
                    cur = a[cur][bit ^ 1][0];
                }
            } else {
                cur = a[cur][0][0];
            }
        }
        // cout << "res : " << res << endl;
        return res;
    }

};

void solve() {
    
    int n; 

    if(debug == 0) {
        cin >> n;
    } else {
        n = rng() % 4 + 2;
    }

    vector<int> a(n), p(n + 1);
    vector<array<int,2>> b(n);
    for(int i = 0; i < n; i++) {
        if(debug == 0) {
            cin >> a[i];
        } else {
            a[i] = rng() % 8;
        }
        p[i+1] = p[i] ^ a[i];
        b[i] = {a[i], i};
    }

    // cout << "p : " << p << endl;

    auto getx = [&](int l, int r) -> int {
        return p[r + 1] ^ p[l];
    };

    sparse<array<int,2>> rmq(b);
    vector<vector<array<int,3>>> ql(n + 1), qr(n + 1); 
    //queries from the left, right, {right, init xor}

    auto aq = [&](int l, int r, int x, int left, int mx) -> void {
        // cout << "aq l : " << l << " r : " << r << " x : " << x << " left : " << left << endl;
        if(left) {
            ql[l].push_back({r, x, mx});
        } else {
            swap(l, r);
            l = n - 1 - l;
            r = n - 1 - r;
            qr[l].push_back({r, x, mx});
        }
        // cout << "ok!" << endl;
    };

    //analyzing interval [l, r]
    auto dnc = [&](auto self, int l, int r) -> void {
        if(l > r) return;
        int m = rmq.query(l, r)[1];
        // cout << "dnc l : " << l << " r : " << r << " m : " << m << endl;
        int left = m - l, right = r - m;
        if(left < right) {
            // cout << "go lefts" << endl;
            for(int i = m; i >= l; i--) {
                // cout << "i : " << i << endl;
                if(i == m) {
                    if(r > m) {
                        aq(m + 2, r + 1, getx(i, m + 1), 1, a[m]);
                    }
                } else {
                    aq(m + 1, r + 1, getx(i, m), 1, a[m]);
                }
            }
        } else {
            // cout << "go rights" << endl;
            for(int i = m; i <= r; i++) {
                // cout << "i : " << i << endl;
                if(i == m) {
                    if(l < m) {
                        aq(l - 1, m - 2, getx(m - 1, i), 0, a[m]);
                    }
                } else {
                    aq(l - 1, m - 1, getx(m, i), 0, a[m]);
                }
            }
        }

        // cout << "ok!!" << endl;

        self(self, l, m - 1);
        self(self, m + 1, r);

    };

    dnc(dnc, 0, n - 1);

    int res = 0;

    auto work = [&](vector<vector<array<int,3>>> &q) -> void {
        int best = 0;
        for(int bit = depth - 1; bit >= 0; bit--) {
            int test = best + (1 << bit);
            int f = 0;
            // cout << "bit : " << bit << " test : " << test << endl;
            trie t(bit, test);

            for(int i = n; i >= 0; i--) {
                // cout << "i : " << i << endl;
                if(i == n) {
                    t.insert(0, i);
                } else {
                    t.insert(a[i], i);
                }
                for(auto [r, x, mx] : q[i]) {
                    // cout << "r : " << r << " x : " << x << " mx : " << mx << endl;
                    if((t.query(x, r) & mx) == test) {
                        f = 1;
                    }
                }
            }
            // cout << "f : " << f << endl;
            if(f) {
                best += 1 << bit;
            }
        }
        res = max(res, best);
    };

    // cout << "start left" << endl;
    work(ql);
    reverse(a.begin(), a.end());
    // cout << "start right" << endl;
    work(qr);

    cout << res << '\n';

    if(debug) {
        int res_slow = -1;
        array<int,2> best = {-1,-1};
        for(int l = 0; l < n; l++) {
            for(int r = l + 1; r < n; r++) {
                int mx = 0, x = 0;
                for(int i = l; i <= r; i++) {
                    x ^= a[i];
                    mx = max(mx, a[i]);
                }
                if((x & mx) > res_slow) {
                    res_slow = x & mx;
                    best = {l, r};
                }
            }
        }

        if(res != res_slow) {
            cout << n << '\n';
            cout << a << '\n';
            cout << "fast : " << res << endl;
            cout << "slow : " << res_slow << endl;
            cout << "best int : " << best << endl;
            assert(0);
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // trie test;
    // test.insert(0, 3);
    // test.insert(3, 2);
    // test.query(3, 2);

    if(debug == 0) {
        int casi; cin >> casi;
        for(int i = 0; i < casi; i++) {
    
            solve();
        }
    } else {
        for(int i = 0; i < 10000; i++) {
            solve();
        }
    }


    return 0;
}