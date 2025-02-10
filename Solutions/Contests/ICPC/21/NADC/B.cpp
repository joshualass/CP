#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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
    void init (const vector<T>& input) {
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

struct SuffixArray {
    string S;
    int N;
    vector<int> sa;
    vector<int> isa;
    vector<int> lcp;

    SuffixArray() {}

    SuffixArray(string _S) {
        N = (S = _S).size() + 1;
        genSa();
        genLcp();        
    }

    void init(string _S) {
        N = (S = _S).size() + 1;
        genSa();
        genLcp();
    }

    void genSa() { //suffix array has size S.size() + 1, starts with s.size()
        sa = vector<int>(N);
        isa = vector<int>(N);
        sa[0] = N-1;
        iota(1 + sa.begin(), sa.end(), 0);
        sort(1 + sa.begin(), sa.end(), [&](int a, int b) {
            return S[a] < S[b]; 
        });
		for(int i = 1; i < N; i++) { 
            int a = sa[i-1];
            int b = sa[i];
			isa[b] = i > 1 && S[a] == S[b] ? isa[a] : i; 
        }
        for(int len = 1; len < N; len *= 2) {
            //by first len chars
            vector<int> s(sa);
            vector<int> is(isa);
            vector<int> pos(N);
            iota(pos.begin(), pos.end(),0);
            for(auto &t : s) {
                int T = t - len;
                if(T >= 0) {
                    sa[pos[isa[T]]++] = T;
                }
            }
            for(int i = 1; i < N; i++) {
                int a = sa[i - 1];
                int b = sa[i];
                isa[b] = is[a] == is[b] && is[a + len] == is[b + len]  ? isa[a] : i;
            }
        }
    }
    
	void genLcp() { // Kasai's Algo
		lcp = vector<int>(N-1); int h = 0;
		for(int b = 0; b < N - 1; b++) { int a = sa[isa[b]-1];
			while (a+h < S.size() && S[a+h] == S[b+h]) ++h;
			lcp[isa[b]-1] = h; if (h) h--; }
		R.init(lcp); /// if we cut off first chars of two strings
		/// with lcp h then remaining portions still have lcp h-1 
	}
	RMQ<int> R; 
	int getLCP(int a, int b) { // lcp of suffixes starting at a,b
		if (a == b) return S.size()-a;
		int l = isa[a], r = isa[b]; if (l > r) swap(l,r);
		return R.query(l,r-1);
	}  
};

template <typename T, T sigma, int L>
struct WaveletTree
{
    struct Node
    {
        unsigned l, r;
        vector<int> x;
    };

    Node t[L];

    unsigned build(vector<T> seq, T a = 0, T b = sigma)
    {
        static unsigned l = 0;

        if (seq.empty())
            return UINT_MAX;

        unsigned node = l++;
        if (a == b)
            return node;

        t[node].x.resize(seq.size());
        T const mid = (a + b) / 2;
        vector<T> left_seq, right_seq;

        for (size_t i = 0; i < seq.size(); ++i)
        {
            if (seq[i] <= mid)
                left_seq.push_back(seq[i]), t[node].x[i] = 1;
            else
                right_seq.push_back(seq[i]);
        }
        for (size_t i = 1; i < seq.size(); ++i)
            t[node].x[i] += t[node].x[i - 1];

        t[node].l = build(left_seq, a, mid);
        t[node].r = build(right_seq, mid + 1, b);
        return node;
    }

    inline int map_left(unsigned node, int i)
    {
        return i >= 0 ? t[node].x[i] - 1 : -1;
    }

    inline int map_right(unsigned node, int i)
    {
        return i >= 0 ? i - t[node].x[i] : -1;
    }

    unsigned rank(T q, int i, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (i == -1)
            return 0;
        if (a == b)
            return i + 1;

        T mid = (a + b) / 2;
        if (q <= mid)
            return rank(q, map_left(node, i), t[node].l, a, mid);
        else
            return rank(q, map_right(node, i), t[node].r, mid + 1, b);
    }

    T quantile(int i, int j, int k, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (a == b)
            return a;
        int c = map_left(node, j) - map_left(node, i - 1);
        if (c >= k)
            return quantile(map_left(node, i - 1) + 1,
                            map_left(node, j), k, t[node].l, a, (a + b) / 2);
        else
            return quantile(map_right(node, i - 1) + 1,
                            map_right(node, j), k - c, t[node].r, (a + b) / 2 + 1, b);
    }

    unsigned count(int i, int j, T x, T y, unsigned node = 0, T a = 0, T b = sigma)
    {
        if (node == UINT_MAX || b < x || a > y)
            return 0;
        if (x <= a && b <= y)
            return j - i + 1;

        return count(map_left(node, i - 1) + 1, map_left(node, j), x, y, t[node].l, a, (a + b) / 2) +
               count(map_right(node, i - 1) + 1, map_right(node, j), x, y, t[node].r, (a + b) / 2 + 1, b);
    }
};

WaveletTree<int, 1000000000, 4000000> tree;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int n = s.size();

    SuffixArray sa(s);
    vector<int> si = sa.sa;
    si.erase(si.begin());

    // cout << "sa suffixes\n";
    // for(int x : si) cout << s.substr(x) << '\n';

    tree.build(si);

    // cout << "si : " << si << '\n';
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        string t; cin >> t;
        int k; cin >> k;
        int l0 = 0, r0 = n;
        while(l0 != r0) {
            int m = (l0 + r0) / 2;
            // cout << "m : " << m << " ss : " << s.substr(si[m],t.size()) << '\n';
            if(t <= s.substr(si[m],t.size())) {
                r0 = m;
            } else {
                l0 = m + 1;
            }
        }
        int l1 = 0, r1 = n;
        while(l1 != r1) {
            int m = (l1 + r1) / 2;
            if(t < s.substr(si[m],t.size())) {
                r1 = m;
            } else {
                l1 = m + 1;
            }
        }
        // cout << "i : " << i << " l0 : " << l0 << " l1 : " << l1 << '\n';
        if(l1 - l0 < k) {
            cout << "-1\n";
            continue;
        }
        cout << tree.quantile(l0,l1-1,k) + 1 << '\n';
    }


    return 0;
}