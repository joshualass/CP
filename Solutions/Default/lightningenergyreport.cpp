#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// https://vjudge.net/problem/UVA-1674

//a relatively dumb implementation of heavy-light decomposition. 
//note that this implementation is not very optimized; you'll probably TLE on tight time constraints. 
//O(log^2(n)) query and modify any path along the tree. 

//if you want to modify this to modify and query across edges, then 

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

//reqs: edges is a valid tree rooted at 0. No cycles.
// template<typename T>
struct LCA {

    RMQ<int> rmq;
    vector<vector<int>> adj;
    vector<int> ids; //stores id of node at i
    vector<int> nodes; //stores node of id at i
    vector<int> euler;
    vector<int> euler_ids;
    int n;

    LCA() {} //default constructor

    //given vector where each node stores its parent
    LCA(const vector<int>& parents) {
        this->n = parents.size();
        adj.assign(n, {});
        for(int i = 1; i < n; i++) {
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
        build();
    }    

    //given adjacency list. untested
    LCA(const vector<vector<int>> &input_adj) {
        this->n = input_adj.size();
        adj = input_adj;
        build();
    }

    void constructor(const vector<vector<int>> &input_adj) {
        this->n = input_adj.size();
        adj = input_adj;
        build();
    }

    void build() {
        euler_ids.assign(n,-1);
        nodes.assign(n,-1);
        ids.assign(n,-1);
        assign_ids();
        euler_tour(0,-1);
        rmq.build(euler);
    }

    //assigns id in a level traversal manner so rmq works
    void assign_ids() {
        queue<pair<int,int>> q; //curr, parent
        int id = 0;
        q.push({0,-1});
        while(q.size()) {
            pair<int,int> p = q.front();
            q.pop();
            ids[p.first] = id;
            nodes[id++] = p.first;
            for(auto x : adj[p.first]) {
                if(x != p.second) {
                    q.push({x,p.first});
                }
            }   
        }

    }   

    void euler_tour(int i, int p) {
        euler_ids[i] = euler.size();
        euler.push_back(ids[i]);
        for(auto x : adj[i]) {
            if(x != p) {
                euler_tour(x,i);
                euler.push_back(ids[i]);
            }
        }
    }

    //finds lca of node l and r [l,r]
    int find_lca(int l, int r) { //reverse order
        return nodes[rmq.query(min(euler_ids[l],euler_ids[r]), max(euler_ids[l],euler_ids[r]))];
    }

};

struct HLD {

    struct SegtreeLazy {
        public:
            int n;
            // int* t;    //stores product of range
            // int* d;    //lazy tree
            // bool* upd;   //upd[i] = true if t[i] needs to be updated
            vector<int> t;
            vector<int> d;
            vector<bool> upd;
            int uneut, qneut;

            //single element modify
            function<int(int, int)> fmodify;

            //k element modify
            function<int(int, int, int)> fmodifyk;

            //product of two elements for query
            function<int(int, int)> fcombine;

            SegtreeLazy(int maxSize, int updateNeutral, int queryNeutral, function<int(int, int)> fmodify, function<int(int, int, int)> fmodifyk, function<int(int, int)> fcombine) {
                n = maxSize;
                uneut = updateNeutral;
                qneut = queryNeutral;

                this -> fmodify = fmodify;
                this -> fmodifyk = fmodifyk;
                this -> fcombine = fcombine;

                //raise n to nearest pow 2
                int x = 1;
                while(x < n) {
                    x <<= 1;
                }
                n = x;

                // t = new int[n * 2];
                // d = new int[n * 2];
                // upd = new bool[n * 2];
                t.assign(n * 2, 0);
                d.assign(n * 2, 0);
                upd.assign(n * 2, 0); 

                //make sure to initialize values
                for(int i = 0; i < n * 2; i++){
                    t[i] = uneut;
                }
                for(int i = 0; i < n * 2; i++){
                    d[i] = uneut;
                    upd[i] = false;
                }
            }

            SegtreeLazy() {
                //do nothing. 
            }

            void modify(int l, int r, int val) {    //modifies the range [l, r)
                _modify(l, r, val, 0, n, 1);
            }

            void modify(int ind, int val) { //modifies the range [ind, ind + 1)
                _modify(ind, ind + 1, val, 0, n, 1);
            }

            int query(int l, int r) {   //queries the range [l, r)
                return _query(l, r, 0, n, 1);
            }

            int query(int ind) {    //queries the range [ind, ind + 1)
                return _query(ind, ind + 1, 0, n, 1);
            }

        private:
            //calculates value of node based off of children
            //k is the amount of values that this node represents. 
            void combine(int ind, int k) {
                if(ind >= n){
                    return;
                }
                int l = ind * 2;
                int r = ind * 2 + 1;
                //make sure children are correct value before calculating
                push(l, k / 2);
                push(r, k / 2);
                t[ind] = fcombine(t[l], t[r]);
            }

            //registers a lazy change into this node
            void apply(int ind, int val) {
                upd[ind] = true;
                d[ind] = fmodify(d[ind], val);
            }

            //applies lazy change to this node
            //k is the amount of values that this node represents. 
            void push(int ind, int k) {
                if(!upd[ind]) {
                    return;
                }
                t[ind] = fmodifyk(t[ind], d[ind], k);
                if(ind < n) {
                    int l = ind * 2;
                    int r = ind * 2 + 1;
                    apply(l, d[ind]);
                    apply(r, d[ind]);
                }
                upd[ind] = false;
                d[ind] = uneut;
            }

            void _modify(int l, int r, int val, int tl, int tr, int ind) {
                if(l == r){
                    return;
                }
                if(upd[ind]){
                    push(ind, tr - tl);
                }
                if(l == tl && r == tr) {
                    apply(ind, val);
                    push(ind, tr - tl);
                    return;
                }
                int mid = tl + (tr - tl) / 2;
                if(l < mid) {
                    _modify(l, min(r, mid), val, tl, mid, ind * 2);
                }
                if(r > mid) {
                    _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
                }
                combine(ind, tr - tl);
            }

            int _query(int l, int r, int tl, int tr, int ind) {
                if(l == r){
                    return qneut;
                }  
                if(upd[ind]) {
                    push(ind, tr - tl);
                }
                if(l == tl && r == tr){
                    return t[ind];
                }
                int mid = tl + (tr - tl) / 2;
                int lans = qneut;
                int rans = qneut;
                if(l < mid) {
                    lans = _query(l, min(r, mid), tl, mid, ind * 2);
                }
                if(r > mid) {
                    rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
                }
                return fcombine(lans, rans);
            }
    };

    int n;

    LCA lca;
    vector<vector<int>> edges;
    vector<bool> toParentHeavy;
    vector<bool> hasOutHeavy;
    vector<int> parent;
    vector<int> subtreeSize;

    SegtreeLazy segt;
    vector<int> segEndInd; //stores the index at which this heavy path ends. 
    vector<int> segParent; //what is the parent node of this heavy path?
    vector<int> segPos;    //stores the index of each node within the segment tree. 

    void calcSubtreeSize(int cur, int p = -1) {
        parent[cur] = p;
        subtreeSize[cur] = 1;
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            calcSubtreeSize(next, cur);
            subtreeSize[cur] += subtreeSize[next];
        }
    }

    void calcHLD(int cur, int p = -1) {
        for(int i = 0; i < edges[cur].size(); i++){
            int next = edges[cur][i];
            if(next == p){
                continue;
            }
            if(subtreeSize[next] > subtreeSize[cur] / 2) {
                hasOutHeavy[cur] = true;
                toParentHeavy[next] = true;
            }
            calcHLD(next, cur);
        }
    }

    HLD(vector<vector<int>> adjList) {
        // this->lca = LCA(n, root, adjList);
        this->lca.constructor(adjList);
        int root = 0;
        this->n = adjList.size();
        
        this->edges = adjList;
        this->parent = vector<int>(n, -1);
        this->subtreeSize = vector<int>(n, 0);
        this->toParentHeavy = vector<bool>(n, false);
        this->hasOutHeavy = vector<bool>(n, false);
        this->calcSubtreeSize(root);
        this->calcHLD(root);

        //create the segment tree needed to do the range updates. 
        //increment modify, sum query
        function<int(int, int)> fmodify = [](const int src, const int val) -> int{return src + val;};
        function<int(int, int, int)> fmodifyk = [](const int src, const int val, const int k) -> int{return src + val * k;};
        function<int(int, int)> fcombine = [](const int a, const int b) -> int{return a + b;};
        this->segt = SegtreeLazy(n, 0, 0, fmodify, fmodifyk, fcombine);
        this->segEndInd = vector<int>(n, -1);
        this->segParent = vector<int>(n, -1);
        this->segPos = vector<int>(n, -1);

        //find the positions of the nodes in the segment tree. 
        int posPtr = 0;
        for(int i = 0; i < n; i++){
            if(this->hasOutHeavy[i]) {
                //we want to have each heavy path be contiguous in the segment tree, so we want to start at the beginning. 
                continue;
            }
            int cur = i;
            vector<int> heavyPath(0);
            heavyPath.push_back(cur);
            this->segPos[cur] = posPtr ++;
            while(toParentHeavy[cur]) {
                cur = parent[cur];
                heavyPath.push_back(cur);
                this->segPos[cur] = posPtr ++;
            }
            cur = parent[cur];
            for(int j = 0; j < heavyPath.size(); j++){
                this->segEndInd[heavyPath[j]] = posPtr;
                this->segParent[heavyPath[j]] = cur;
            }
        }
    }

    void modify(int a, int b, int val) {
        int _lca = this->lca.find_lca(a, b);
        _modify(a, _lca, val);
        _modify(b, _lca, val);
        this->segt.modify(this->segPos[_lca], val);
    }

    void modify(int a, int val) {
        this->segt.modify(this->segPos[a], val);
    }

    int query(int a, int b) {
        int _lca = this->lca.find_lca(a, b);
        int ret = this->segt.qneut;
        ret = this->segt.fcombine(ret, _query(a, _lca));
        ret = this->segt.fcombine(ret, _query(b, _lca));
        ret = this->segt.fcombine(ret, this->segt.query(this->segPos[_lca]));
        return ret;
    }

    int query(int a) {
        return this->segt.query(this->segPos[a]);
    }

    private:
        void _modify(int a, int _lca, int val) {
            //while a and _lca aren't in the same heavy path
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                //modify until the end of the segment a belongs to. 
                this->segt.modify(this->segPos[a], this->segEndInd[a], val);
                a = this->segParent[a];
            }
            //a and _lca are in the same heavy path. Now, just modify the segment from a to _lca, not including _lca. 
            this->segt.modify(this->segPos[a], this->segPos[_lca], val);
        }

        int _query(int a, int _lca) {
            int ret = this->segt.qneut;
            while(this->segEndInd[a] != this->segEndInd[_lca]) {
                ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segEndInd[a]));
                a = this->segParent[a];
            }
            ret = this->segt.fcombine(ret, this->segt.query(this->segPos[a], this->segPos[_lca]));
            return ret;
        }
};

void solve() {
    
    int n; cin >> n;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n- 1 ; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);

    }
    HLD hld(adj);

    int q; cin >> q;

    for(int i = 0; i < q; i++) {
        int a, b, c; cin >> a >> b >> c;

        hld.modify(a,b,c);

    }

    for(int i = 0; i < n; i++) {
        cout << hld.query(i) << '\n';
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int casi; cin >> casi;
    // while(casi-->0) solve();

    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cout << "Case #" << i << ":\n";
        solve();
    }

    return 0;
}