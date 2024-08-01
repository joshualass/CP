#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
Handle a couple of cases
if the number of operations is not greater than the length of the array, we can just do increasing red to blue operations for all elements doing the largest on the smallest element
If number of operations is greater, we want to end with having the last n operations be red to blue operations. Changing an element from red to blue will always decrease it by 1 each time.
If the pairty of k is that of n, then we can spend last n operations doing red to blue greedily, and then greedily do operations to the last elements doing 2 operations for every decrease of 1
If the parity of k is not that of n, then we spend last n - 1 operations doing red to blue greedily, and then once again greedily decrease by 1 for every 2 elements left. 
*/

//could use RMQ here, but template is annoying >.<
template<typename T>
struct Tree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a,b);
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
            if(curr & 1) { //handles non-communative operations
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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, q; cin >> n >> q;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    ll samesum = accumulate(a.begin(), a.end(), 0LL) - n * (n - 1) / 2;
    ll samemin = INT_MAX;
    ll diffsum = accumulate(a.begin(), a.end(), 0LL) - (n - 1) * (n - 2) / 2;
    ll diffmin = INT_MAX;

    Tree<ll> initialTree(n);
    Tree<ll> sameTree(n);

    for(ll i = 0; i < n; i++) {
        initialTree.update(i, a[i]);
        sameTree.update(i, a[i] - i);
        samemin = min(samemin, a[i] - i);
        if(i != n - 1) {
            diffmin = min(diffmin, a[i] - i);
        }
    }

    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        if(k <= n) {
            cout << min(sameTree.query(0,k) + k, initialTree.query(k, n)) << " \n"[i == q - 1];
        } else {
            if((k - n) % 2 == 0) {
                ll remain = (k - n) / 2;
                ll overmin = samesum - samemin * n;
                remain -= min(remain, overmin);
                cout << samemin + k - (remain + n - 1) / n << " \n"[i == q - 1];
            } else {
                // cout << "k : " << k << '\n';
                ll remain = (k - (n - 1)) / 2;
                ll currsum = diffsum + k * (n - 1);
                ll currmin = min(a.back(), diffmin + k);
                ll overmin = currsum - currmin * n;
                // cout << "remain : " << remain << " currsum : " << currsum << " currmin : " << currmin << " overmin : " << overmin << '\n';
                remain -= min(remain, overmin);
                cout << currmin - (remain + n - 1) / n << " \n"[i == q - 1];
                // cout << '\n';
            }
        }
    }

    return 0;
}