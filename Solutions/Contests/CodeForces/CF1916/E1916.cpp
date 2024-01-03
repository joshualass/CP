#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T>
struct SegtreeLazy {
    public:
        int n;
        T* t;    //stores product of range
        T* d;    //lazy tree
        bool* upd;  //marks whether or not a lazy change is here
        T uneut, qneut;

        //single element modify
        function<T(T, T)> fmodify;

        //k element modify
        function<T(T, T, int)> fmodifyk;

        //product of two elements for query
        function<T(T, T)> fcombine;

        SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T, int)> fmodifyk, function<T(T, T)> fcombine) {
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

            t = new T[n * 2];
            d = new T[n * 2];
            upd = new bool[n * 2];

            //make sure to initialize values
            for(int i = 0; i < n * 2; i++){
                t[i] = uneut;
            }
            for(int i = 0; i < n * 2; i++){
                d[i] = uneut;
                upd[i] = false;
            }
        }

        void modify(int l, int r, T val) {    //modifies the range [l, r)
            _modify(l, r, val, 0, n, 1);
        }

        void modify(int ind, T val) { //modifies the range [ind, ind + 1)
            _modify(ind, ind + 1, val, 0, n, 1);
        }

        T query(int l, int r) {   //queries the range [l, r)
            return _query(l, r, 0, n, 1);
        }

        T query(int ind) {    //queries the range [ind, ind + 1)
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

        //registers a lazy change llo this node
        void apply(int ind, T val) {
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

        void _modify(int l, int r, T val, int tl, int tr, int ind) {
            if(l == r){
                return;
            }
            if(upd[ind]) {
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

        T _query(int l, int r, int tl, int tr, int ind) {
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
            T lans = qneut;
            T rans = qneut;
            if(l < mid) {
                lans = _query(l, min(r, mid), tl, mid, ind * 2);
            }
            if(r > mid) {
                rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
            }
            return fcombine(lans, rans);
        }
};

const int MAXN = 3e5;
int visitTime [MAXN];
int subtreeSize [MAXN];
int colors[MAXN];
stack<int> curr_colors[MAXN];
vector<int> adj[MAXN];
vector<int> childcolors[MAXN];

void euler_tour(int i, int p, int &iVisitTime) {
    visitTime[i] = iVisitTime;
    iVisitTime++;
    for(int child : adj[i]) {
        euler_tour(child, i, iVisitTime);
    }
    subtreeSize[i] = iVisitTime - visitTime[i];
}

void dfs(int i, int p) {
    int color = colors[i];
    if(curr_colors[color].size()) {
        int v = curr_colors[color].top();
        childcolors[v].push_back(i);
    }
    curr_colors[color].push(i);
    for(int child : adj[i]) {
        if(child != p) {
            dfs(child, i);
        }
    }
    curr_colors[color].pop();
}

void dfs2(int i, int p, SegtreeLazy<ll> &tree, ll &ans) {
    for(int child : adj[i]) {
        dfs2(child,i,tree,ans);
    }
    tree.modify(visitTime[i], visitTime[i] + subtreeSize[i],1);
    for(int childcolor : childcolors[i]) {
        tree.modify(visitTime[childcolor],visitTime[childcolor] + subtreeSize[childcolor],-1);
    }
    ll best1 = 1;
    ll best2 = 1;
    for(int child : adj[i]) {
        ll next = tree.query(visitTime[child], visitTime[child] + subtreeSize[child]);
        if(next > best2) {
            best2 = next;
        }
        if(best2 > best1) swap(best1,best2);
    }
    ans = max(ans, best1 * best2);
}

void solve() {
    int n; cin >> n;
    for(int i = 1; i < n; i++) {
        int parent; cin >> parent;
        parent--;
        adj[parent].push_back(i);
    }
    int iVisitTime = 0;

    euler_tour(0, -1, iVisitTime);

    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        num--;
        colors[i] = num;
    }

    dfs(0,-1);

    function<ll(ll, ll)> modifyElement = [](const ll src, const ll val) -> ll{return src + val;};
    function<ll(ll, ll, ll)> modifyRange = [](const ll src, const ll val, const ll k) -> ll{return src + val;};
    function<ll(ll, ll)> queryType = [](const ll a, const ll b) -> ll{return max(a, b);};

    SegtreeLazy<ll> tree(n,0,0,modifyElement,modifyRange,queryType);
    ll ans = -1;

    dfs2(0,-1, tree, ans);
    cout << ans << '\n';
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        childcolors[i].clear();
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}